 


#include "EndPortal.h"
#include "UserPlayer.h"

// Sets default values
AEndPortal::AEndPortal()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));

	SetRootComponent(Box);
	Effect->SetupAttachment(Box);
}

// Called when the game starts or when spawned
void AEndPortal::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AEndPortal::OnOverlapPortal);
}

// Called every frame
void AEndPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndPortal::OnOverlapPortal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)						return;
	if (!OtherActor->IsA<AUserPlayer>())	return;

	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AUserPlayer* userPlayer = Cast<AUserPlayer>(OtherActor);
	AUserController* userController = Cast<AUserController>(userPlayer->GetController());
	userController->bShowMouseCursor = true;
	UUIEnding* EndingMenu = userPlayer->GetEndingMenu();
	EndingMenu->SetSeconds(gameInstance->PlayedTime);
	EndingMenu->SetVisibility(ESlateVisibility::Visible);
}

