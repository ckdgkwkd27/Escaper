#pragma once
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DataTable.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EDir : uint8 {
	Front,
	Back,
	Left,
	Right,
	Up,
	Down
};

void PrintViewport(float fTime, const FColor& Color, const FString& strText);
