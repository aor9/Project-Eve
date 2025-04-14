#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueStruct.generated.h"

USTRUCT()
struct FOptionData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndDialogue = false;
};

USTRUCT()
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextRow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPCName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* NPCIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndDialogue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FOptionData> OptionData;

	// 이벤트 트리거 용 Tag : ex) shop, quest, 아이템 지급 등
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TriggerEventName;
};
