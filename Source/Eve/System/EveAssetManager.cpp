// Copyright aor9


#include "System/EveAssetManager.h"


UEveAssetManager::UEveAssetManager() : Super()
{
}

UEveAssetManager& UEveAssetManager::Get()
{
	if (UEveAssetManager* Singleton = Cast<UEveAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Can't find UEveAssetManager"));

	return *NewObject<UEveAssetManager>();
}

void UEveAssetManager::Initialize()
{
	Get().LoadPreloadAssets();
}

void UEveAssetManager::LoadSyncByPath(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		UObject* LoadedAsset = AssetPath.ResolveObject();
		if (LoadedAsset == nullptr)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
			}
			else
			{
				LoadedAsset = AssetPath.TryLoad();
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAsset(AssetPath.GetAssetFName(), LoadedAsset);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
		}
	}
}

void UEveAssetManager::LoadSyncByName(const FName& AssetName)
{
	UEveAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadSyncByPath(AssetPath);
}

void UEveAssetManager::AddLoadedAsset(const FName& AssetName, const UObject* Asset)
{
	if (AssetName.IsValid() && Asset)
	{
		//FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);

		if (NameToLoadedAsset.Contains(AssetName) == false)
		{
			NameToLoadedAsset.Add(AssetName, Asset);
		}
	}
}

void UEveAssetManager::LoadSyncByLabel(const FName& Label)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UEveAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;

	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabel(Label);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadSyncByPath(AssetPath);
		if (AssetPath.IsValid())
		{
			AssetPaths.Emplace(AssetPath);
		}
	}

	GetStreamableManager().RequestSyncLoad(AssetPaths);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			if (UObject* LoadedAsset = AssetPath.ResolveObject())
			{
				Get().AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
			}
		}
	}
}

void UEveAssetManager::LoadAsyncByPath(const FSoftObjectPath& AssetPath, FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	if (AssetPath.IsValid())
	{
		if (UObject* LoadedAsset = AssetPath.ResolveObject())
		{
			Get().AddLoadedAsset(AssetPath.GetAssetFName(), LoadedAsset);
		}
		else
		{
			TArray<FSoftObjectPath> AssetPaths;
			AssetPaths.Add(AssetPath);

			TSharedPtr<FStreamableHandle> Handle = GetStreamableManager().RequestAsyncLoad(AssetPaths);

			Handle->BindCompleteDelegate(FStreamableDelegate::CreateLambda([AssetName = AssetPath.GetAssetFName(), AssetPath, CompleteDelegate = MoveTemp(CompletedDelegate)]()
				{
					UObject* LoadedAsset = AssetPath.ResolveObject();
					Get().AddLoadedAsset(AssetName, LoadedAsset);
					if (CompleteDelegate.IsBound())
						CompleteDelegate.Execute(AssetName, LoadedAsset);
				}));
		}
	}
}

void UEveAssetManager::LoadAsyncByName(const FName& AssetName, FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UEveAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadAsyncByPath(AssetPath, CompletedDelegate);
}

void UEveAssetManager::ReleaseByPath(const FSoftObjectPath& AssetPath)
{
	FName AssetName = AssetPath.GetAssetFName();
	ReleaseByName(AssetName);
}

void UEveAssetManager::ReleaseByName(const FName& AssetName)
{
	UEveAssetManager& AssetManager = Get();
	if (AssetManager.NameToLoadedAsset.Contains(AssetName))
	{
		AssetManager.NameToLoadedAsset.Remove(AssetName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
	}
}

void UEveAssetManager::ReleaseByLabel(const FName& Label)
{
	UEveAssetManager& AssetManager = Get();
	UEveAssetData* LoadedAssetData = AssetManager.LoadedAssetData;
	const FAssetSet& AssetSet = LoadedAssetData->GetAssetSetByLabel(Label);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FName& AssetName = AssetEntry.AssetName;
		if (AssetManager.NameToLoadedAsset.Contains(AssetName))
		{
			AssetManager.NameToLoadedAsset.Remove(AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
		}
	}
}

void UEveAssetManager::ReleaseAll()
{
	UEveAssetManager& AssetManager = Get();
	AssetManager.NameToLoadedAsset.Reset();
}

void UEveAssetManager::LoadPreloadAssets()
{
	if (LoadedAssetData)
		return;

	UEveAssetData* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UEveAssetData::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UEveAssetData>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		LoadedAssetData = AssetData;
		LoadSyncByLabel("Preload");
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load AssetData asset type [%s]."), *PrimaryAssetType.ToString());
	}
}