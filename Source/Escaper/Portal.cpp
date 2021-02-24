 


#include "Portal.h"
#include "UserPlayer.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	
	SetRootComponent(Box);
	Effect->SetupAttachment(Box);

	bLocked = false;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (bLocked && !gameInstance->bPortalLocked)
		bLocked = false;

	Box->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapPortal);

	if (bLocked) {
		Effect->SetNiagaraVariableLinearColor(FString("User.Color01"), FLinearColor::Gray);
		Effect->SetNiagaraVariableLinearColor(FString("User.Color02"), FLinearColor::Gray);
	}

}

void APortal::OnOverlapPortal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (LoadingLevel.IsEmpty())				return;
	if (bLocked)							return;
	if (!OtherActor)						return;
	if (!OtherActor->IsA<AUserPlayer>())	return;

	gameInstance->SpawnLocation = SpawnLocation;
	gameInstance->SpawnRotation = SpawnRoatation;
	
	UGameplayStatics::OpenLevel(GetWorld(), *LoadingLevel);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!gameInstance->bPortalLocked) {
		bLocked = false;
		Effect->SetNiagaraVariableLinearColor(FString("User.Color01"), FLinearColor::Blue);
		Effect->SetNiagaraVariableLinearColor(FString("User.Color02"), FLinearColor::Blue);
	}
}

