#include "GameInfo.h"

void PrintViewport(float fTime, const FColor& Color,
	const FString& strText)
{
	GEngine->AddOnScreenDebugMessage(-1, fTime, Color, strText);
}
