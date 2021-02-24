 


#include "PickupItem.h"
#include "UserPlayer.h"
#include "EscaperGameInstance.h"

// Sets default values
APickupItem::APickupItem()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SetRootComponent(Box);
	Mesh->SetupAttachment(Box);  
	Particle->SetupAttachment(Mesh);

	//Particle 정보 
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/InventoryForBR/FX/PickupEffect.PickupEffect'"));
	if (ParticleAsset.Succeeded())
		Particle->SetTemplate(ParticleAsset.Object);

	//PickupItem 정보 
	static ConstructorHelpers::FClassFinder<UUIPickupItem> pickupUIAsset(TEXT("WidgetBlueprint'/Game/UI/BPPickupItemUI.BPPickupItemUI_C'"));
	if (pickupUIAsset.Succeeded())
		pickupUIClass = pickupUIAsset.Class;


	Box->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel7);
	//Box->SetCollisionProfileName(FName("Pickup"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();

	UEscaperGameInstance* gameInstance = Cast<UEscaperGameInstance>(GetGameInstance()); 
	if (gameInstance->PickupSpawnMap.Find(GetItemName().ToString()))
		Destroy();

	if (IsValid(pickupUIClass))
		pickupUI = Cast<UUIPickupItem>(CreateWidget(GetWorld(), pickupUIClass));

	if (IsValid(pickupUI))
	{
		if (Type == ItemType::WEAPON) {
			if (IsValid(weapon)) {
				pickupUI->SetTitle(weapon->GetTitle());
				pickupUI->SetRarityAndCategory(weapon->GetRarityAndCategory());
				pickupUI->SetDescription(weapon->GetDescription());
				pickupUI->SetIconImageFromPath(weapon->GetIconPath());
				pickupUI->SetRarityColor(weapon->GetRarityColor());
			}
			else
				UE_LOG(LogTemp, Error, TEXT("Weapon is NULL"));
		}
		else {
			if (IsValid(interactClue)) {
				pickupUI->SetTitle(interactClue->GetTitle());
				pickupUI->SetRarityAndCategory(interactClue->GetRarityAndCategory());
				pickupUI->SetDescription(interactClue->GetDescription());
				pickupUI->SetIconImageFromPath(interactClue->GetIconPath());
			}
			else
				UE_LOG(LogTemp, Error, TEXT("InteractClue is NULL"));
		}
	
		pickupUI->AddToViewport();
		pickupUI->SetVisibility(ESlateVisibility::Hidden); 
	}
}

void APickupItem::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::showUI()
{
	if (IsValid(pickupUI))
	{		
		pickupUI->SetRenderTranslation(FVector2D(-400.f, -50.f));
		pickupUI->SetVisibility(ESlateVisibility::Visible); 
	}
}

void APickupItem::deleteUI()
{
	if(pickupUI->IsInViewport())
		pickupUI->SetVisibility(ESlateVisibility::Hidden);
}

