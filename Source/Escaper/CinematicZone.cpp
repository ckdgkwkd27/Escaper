 


#include "CinematicZone.h"

// Sets default values
ACinematicZone::ACinematicZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void ACinematicZone::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACinematicZone::TriggerBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACinematicZone::TriggerEndOverlap);

	int32 iCount = CameraArray.Num();

	for (int32 i = 0; i < iCount - 1; ++i)
	{
		FVector	vDir = CameraArray[i + 1]->GetActorLocation() -
			CameraArray[i]->GetActorLocation();
		vDir.Normalize();

		CameraArray[i]->SetActorRotation(vDir.Rotation());
	}
}

// Called every frame
void ACinematicZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACinematicZone::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StartEvent();
}

void ACinematicZone::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EndEvent();
}

void ACinematicZone::StartEvent()
{
	PointIndex = 0;

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	Controller->SetViewTargetWithBlend(Controller->GetPawn(), 2.f,
		EViewTargetBlendFunction::VTBlend_EaseInOut, 0.5f);
}

void ACinematicZone::EndEvent()
{
	PointIndex = 0;

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	Controller->SetViewTargetWithBlend(Controller->GetPawn(), 2.f,
		EViewTargetBlendFunction::VTBlend_EaseInOut, 0.5f);
}

void ACinematicZone::CameraBlendEnd()
{
	GetWorldTimerManager().ClearTimer(BlendTimerHandle);

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	Controller->SetViewTargetWithBlend(CameraArray[PointIndex], 1.f,
		EViewTargetBlendFunction::VTBlend_EaseInOut, 0.5f);

	// 블렌드가 종료될때 호출될 타이머를 생성한다.
	GetWorldTimerManager().SetTimer(ChangeTimerHandle, this,
		&ACinematicZone::CameraChangeEnd, 1.f, true);
}

void ACinematicZone::CameraChangeEnd()
{
	GetWorldTimerManager().ClearTimer(ChangeTimerHandle);

	++PointIndex;

	if (PointIndex >= CameraArray.Num())
		EndEvent();

	else
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();

		Controller->SetViewTargetWithBlend(CameraArray[PointIndex], 1.f,
			EViewTargetBlendFunction::VTBlend_EaseInOut, 0.5f);

		// 블렌드가 종료될때 호출될 타이머를 생성한다.
		GetWorldTimerManager().SetTimer(ChangeTimerHandle, this,
			&ACinematicZone::CameraChangeEnd, 1.f, true);
	}
}

