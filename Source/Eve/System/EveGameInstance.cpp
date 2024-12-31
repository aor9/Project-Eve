// Copyright aor9


#include "System/EveGameInstance.h"

#include "EveAssetManager.h"


UEveGameInstance::UEveGameInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UEveGameInstance::Init()
{
	Super::Init();

	// TODO: 게임 전체에서 공통으로 사용되는 에셋이거나 초기화에 필수적인 에셋을 관리하는 용도로 적합, 비동기 로드와 Asset Manager를 활용해 성능과 메모리 사용을 최적화하기.
	UEveAssetManager::Initialize();
}

void UEveGameInstance::Shutdown()
{
	Super::Shutdown();
}
