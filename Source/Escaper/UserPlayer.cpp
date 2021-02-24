 


#include "UserPlayer.h"
#include "UserAnim.h"
#include "Interactable.h"
#include "Door.h"
#include "EscaperGameInstance.h"
#include "UserController.h"
#include "Weapon_AR.h"
#include "Weapon_SMG.h"
#include "Weapon_Pistol.h"
#include "DrawDebugHelpers.h"

// Sets default values
AUserPlayer::AUserPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsEquipped = false;

	iMAX_HP = 100;
	iHP = 100;

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Cameras = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Arm->SetupAttachment(GetMesh());
	Cameras->SetupAttachment(Arm);

	Arm->bInheritPitch = true;
	Arm->bInheritRoll = true;
	Arm->bInheritYaw = true;
	Arm->bUsePawnControlRotation = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory")); 

	// anim 관련 설정.
	static ConstructorHelpers::FClassFinder<UUserAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BPUserAnim.BPUserAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);


	fAttack_time = 0.f;
	fAttack_time_max = 0.25f;
	bAttackEnable = true;

	bInventoryOpened = false;
	bPauseMenuOpened = false;

}

// Called when the game starts or when spawned
void AUserPlayer::BeginPlay()
{
	Super::BeginPlay();
	UserAnim = Cast<UUserAnim>(GetMesh()->GetAnimInstance());
	GetCharacterMovement()->MaxWalkSpeed = 800.f;

	//InventoryComponent->SetFlags(EObjectFlags::RF_Standalone);

	GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode)) {
		playerHUD = GameMode->GetPlayerHUD();

		Inventory = GameMode->GetInventory();
		Inventory->SetVisibility(ESlateVisibility::Hidden);

		DeathMenu = GameMode->GetDeathMenu();
		DeathMenu->SetVisibility(ESlateVisibility::Hidden);

		PauseMenu = GameMode->GetPauseMenu();
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		EndingMenu = GameMode->GetEndingMenu();
		EndingMenu->SetVisibility(ESlateVisibility::Hidden);
	}
	
	/*****************************************************************************************/

	//Load from game instance 
	gameInstance = Cast<UEscaperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//Player 위치 정보
	FVector location = gameInstance->SpawnLocation;
	FRotator rotation = gameInstance->SpawnRotation;

	if(location != FVector(0))
		TeleportTo(gameInstance->SpawnLocation, gameInstance->SpawnRotation);
	AUserController* controller = Cast<AUserController>(GetController());
	controller->SetControlRotation(gameInstance->SpawnRotation);

	//Player HP 정보
	if (gameInstance->GetHP() != -1) 
		SetHealth(gameInstance->GetHP());

	//Weapon Slot
	for (auto wp : gameInstance->GetWeaponClasses()) {
		GenerateWeapon(wp);
		SetWeapon();
		//weapon->getbullet(gameinstance->getbullet)
		UserAnim->SetEquipped(true);
		playerHUD->AddToSlot(Weapon);
	}

}

void AUserPlayer::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	//InventoryComponent = nullptr;
}

// Called every frame
void AUserPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//공격 불가상태시 딜레이
	if (!bAttackEnable) {
		if (fAttack_time_max <= fAttack_time) {
			fAttack_time = 0.f;
			bAttackEnable = true;
		}
		fAttack_time += DeltaTime;
	}

	FVector start, end;
	FVector outLocation;
	FRotator outRotation;
	GetActorEyesViewPoint(outLocation, outRotation);

	//outRotation.Yaw += 15.f;

	start = outLocation;
	end = outRotation.Vector() * 300.f + start;

	FHitResult hitResult;
	FHitResult InteractResult;
	FCollisionQueryParams  tColParams(NAME_None, false, this);
	FCollisionObjectQueryParams collObjQueryParams(ECC_GameTraceChannel7);
	FCollisionObjectQueryParams InteractQueryParams(ECC_GameTraceChannel6);

	bIsPickupItem = GetWorld()->LineTraceSingleByChannel(hitResult, start, end,
		ECollisionChannel::ECC_GameTraceChannel1, tColParams);

	bool bIsInteractable = GetWorld()->SweepSingleByObjectType(InteractResult, start, end, FQuat::Identity,
		InteractQueryParams, FCollisionShape::MakeSphere(20.f), tColParams);

	if (bIsPickupItem) {
		//액터가 아닐경우
		if (!hitResult.Actor.IsValid()) {
			if(pi)
				pi->deleteUI();
			pi = nullptr;
		}
		else if (hitResult.Actor.Get()->IsA<APickupItem>()) {
			pi = Cast<APickupItem>(hitResult.GetActor());
			pi->showUI();
		}
		else {
			if (pi)
				pi->deleteUI();
			pi = nullptr;
		}
	} 
	
	else {
		if(pi)
			pi->deleteUI();
	}

	if (bIsInteractable) 
		playerHUD->SetNotiVisibility(ESlateVisibility::Visible);
	else
		playerHUD->SetNotiVisibility(ESlateVisibility::Hidden);
}

// Called to bind functionality to input
void AUserPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this,
		&AUserPlayer::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this,
		&AUserPlayer::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this,
		&AUserPlayer::RotationZ);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this,
		&AUserPlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::JumpKey);
	PlayerInputComponent->BindAction(TEXT("NormalAttack"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::NormalAttack);
	PlayerInputComponent->BindAction(TEXT("NormalAttack"),
		EInputEvent::IE_Released, this, &AUserPlayer::EndAttack);
	PlayerInputComponent->BindAction(TEXT("Interact"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::Interact);
	PlayerInputComponent->BindAction(TEXT("Reload"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::Reload);
	PlayerInputComponent->BindAction(TEXT("Equip"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::Equip);
	PlayerInputComponent->BindAction(TEXT("SelectWeapon"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::SelectWeapon);
	PlayerInputComponent->BindAction(TEXT("OpenInventory"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::OpenInventory);
	PlayerInputComponent->BindAction(TEXT("OpenPauseMenu"),
		EInputEvent::IE_Pressed, this, &AUserPlayer::OpenPauseMenu);
}

void AUserPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AUserPlayer::SetHealth(int32 hp)
{
	iHP = hp;

	if (IsValid(playerHUD))
		playerHUD->SetHealth(hp);
}

void AUserPlayer::SetWeapon() {
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("weapon_hand_r"));

	bIsEquipped = true;
}

void AUserPlayer::GenerateWeapon(TSubclassOf<AWeapon> weapon) {
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (IsValid(Weapon)) {
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		FVector WeaponLocation = Weapon->GetActorLocation();
		WeaponLocation.Z -= 1000.f;
	}

	Weapon = GetWorld()->SpawnActor<AWeapon>(weapon, FVector::ZeroVector,
		FRotator::ZeroRotator, params);
}

void AUserPlayer::ChangeAnim(EPlayerAnim anim) {
	UserAnim->ChangeAnim(anim);
}

float AUserPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	iHP -= (int32)fDamage;

	if (iHP <= 0) {
		iHP = 0;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ChangeAnim(EPlayerAnim::Death);

		AUserController* userController = Cast<AUserController>(GetController());
		DeathMenu->SetVisibility(ESlateVisibility::Visible);
		userController->bShowMouseCursor = true;
	}

	//update to game instance
	gameInstance->SetHP(iHP);

	return fDamage;
}

void AUserPlayer::MoveFront(float fScale)
{
	if (!bStartAnimation)
		return;

	AddMovementInput(GetActorForwardVector(), fScale);

	if (IsValid(UserAnim)) {
		if (fScale > 0.f)
			UserAnim->SetMoveDir(EDir::Front);
		else if (fScale < 0.f)
			UserAnim->SetMoveDir(EDir::Back);
	}
}

void AUserPlayer::MoveSide(float fScale)
{
	if (!bStartAnimation)
		return;

	AddMovementInput(GetActorRightVector(), fScale);

	if (IsValid(UserAnim)) {
		if (fScale > 0.f)
			UserAnim->SetMoveDir(EDir::Right);
		else if (fScale < 0.f)
			UserAnim->SetMoveDir(EDir::Left);
	}

}

void AUserPlayer::RotationZ(float fScale)
{
	if (!bStartAnimation)
		return;
	AddControllerYawInput(fScale);
	//SetActorRotation(GetControlRotation().Quaternion());
}

void AUserPlayer::LookUp(float fScale) {
	if (!bStartAnimation)
		return;
	AddControllerPitchInput(-fScale);
}

void AUserPlayer::JumpKey()
{
	if (!bStartAnimation)
		return;
	if (IsValid(UserAnim))
		UserAnim->Jump();

	Jump();
}

void AUserPlayer::Fire()
{
	FVector vPos;
	FRotator Rot;
	GetActorEyesViewPoint(vPos, Rot);
	vPos.Y += 20.f;
	vPos.Z -= 20.f;
	Rot.Pitch -= 7.f;
	
	if (!IsValid(Weapon))
		return;

	if (Weapon->GetBullet() > 0)
		Weapon->StartFire(this, vPos, Rot);
	else {
		USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/emptygun.emptygun'"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());
	}
}

void AUserPlayer::NormalAttack()
{
	if (!bAttackEnable)
		return;

	if (!bStartAnimation)
		return;

	if (!bIsEquipped)
		return;
	
	if (IsValid(UserAnim)) {
		UserAnim->NormalAttack();
		Fire();
	}

	bAttackEnable = false;
}

void AUserPlayer::EndAttack() {
	if (!bIsEquipped)
		return;

	if(IsValid(Weapon))
		Weapon->EndFire();

	UserAnim->ChangeAnim(EPlayerAnim::Idle);
}

void AUserPlayer::Interact()
{
	FVector	vStart = GetActorLocation();
	FVector	vDir = GetActorForwardVector();
	float	fDistance = Arm->TargetArmLength + 100.f;
	FVector	vEnd = vStart + vDir * fDistance;

	FCollisionQueryParams  tColParams(NAME_None, false, this);
	FHitResult hitResult;

	//Interactable이랑 콜리젼이 일어나면 그곳의 Interact 함수 실행
	bool bCollision = GetWorld()->LineTraceSingleByChannel(hitResult, vStart,
		vEnd, ECollisionChannel::ECC_GameTraceChannel5, tColParams);

	if (bCollision) {
		if(hitResult.GetActor()->IsA<ADoor>())
			UE_LOG(LogTemp, Warning, TEXT("#IS INTERACTABLE"));
		AInteractable *itact = Cast<AInteractable>(hitResult.GetActor());
		itact->Interact(); 
	}
}

void AUserPlayer::Reload()
{
	if (!bStartAnimation)
		return;

	if (IsValid(UserAnim)) {
		UserAnim->Reload();
		USoundBase* SoundAsset = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Weapons/Effect/gunreload.gunreload'"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundAsset, GetActorLocation());
	}
}

void AUserPlayer::ReloadBullet() {
	int addedBullet = Weapon->GetBulletWhole() - Weapon->GetBullet();
	int remainBullet = Weapon->GetMaxBullet() - addedBullet;
	if (remainBullet < 0) remainBullet = 0;
	if (Weapon->GetBullet() + Weapon->GetMaxBullet() <= Weapon->GetBulletWhole()) {
		addedBullet = Weapon->GetMaxBullet();
		remainBullet = 0;
	}

	Weapon->SetBullet(Weapon->GetBullet() + addedBullet, remainBullet);
	playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());


}

void AUserPlayer::Equip()
{
	// Weapon이면 이걸로, 단순 아이템이면 따로 만들고 인벤토리만 추가.
	if (bIsPickupItem) {
		if (!IsValid(pi))
			return;
		if (pi->GetType() == ItemType::WEAPON) {
			GenerateWeapon(pi->GetWeaponClass());
			SetWeapon();
			playerHUD->AddToSlot(Weapon);

			//custom 
			CollectedWeapons.Add(Weapon);

			//update to game instance
			gameInstance->SetWeapon(pi->GetWeaponClass());

			if (IsValid(pi)) {
				pi->deleteUI();
				pi->Destroy();
			}
			UserAnim->SetEquipped(true);
			playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());
		}
		else {
			UItemObject* addItem = pi->GetItemObject();
			if (IsValid(addItem))
				InventoryComponent->AddItem(addItem);

			//pi->AddtoInventory();

			if (IsValid(pi)) {
				pi->deleteUI();
				pi->Destroy();
			}
		}
		gameInstance->PickupSpawnMap.Add(pi->GetItemName().ToString(), true);
	}
} 

void AUserPlayer::SelectWeapon() {

	//1번키 pressed
	bool pressed1 = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(FKey(FName("One")));
	if (pressed1) {
		if (!IsValid(playerHUD->GetSlotInfo(0)))
			return;
		if (IsValid(Weapon)) 
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		Weapon = playerHUD->GetSlotInfo(0);
		if (IsValid(Weapon)) {
			SetWeapon();
			playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());

			gameInstance->SetWeaponName(Weapon->GetName());
		}
	}

	//2번키 pressed
	bool pressed2 = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(FKey(FName("Two")));
	if (pressed2) {
		if (!IsValid(playerHUD->GetSlotInfo(1)))
			return;
		if (IsValid(Weapon)) 
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		Weapon = playerHUD->GetSlotInfo(1);
		if (IsValid(Weapon)) {
			SetWeapon();
			playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());

			gameInstance->SetWeaponName(Weapon->GetName());
		}
	}

	//3번키 pressed
	bool pressed3 = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(FKey(FName("Three")));
	if (pressed3) {
		if (!IsValid(playerHUD->GetSlotInfo(2)))
			return;
		if (IsValid(Weapon)) 
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		Weapon = playerHUD->GetSlotInfo(2);
		if (IsValid(Weapon)) {
			SetWeapon();
			playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());

			gameInstance->SetWeaponName(Weapon->GetName());
		}
	}

	//4번키 pressed
	bool pressed4 = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(FKey(FName("Four")));
	if (pressed4) {
		if (!IsValid(playerHUD->GetSlotInfo(3)))
			return;
		if (IsValid(Weapon))
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

		Weapon = playerHUD->GetSlotInfo(3);
		if (IsValid(Weapon)) {
			SetWeapon();
			playerHUD->SetBullet(Weapon->GetBullet(), Weapon->GetMaxBullet());

			gameInstance->SetWeaponName(Weapon->GetName());
		}
	}

	
}

void AUserPlayer::OpenInventory()
{
	AUserController* userController = Cast<AUserController>(GetController());
	if (!bInventoryOpened) {
		bInventoryOpened = true;
		userController->bShowMouseCursor = true;
		Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		bInventoryOpened = false;
		userController->bShowMouseCursor = false;
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AUserPlayer::OpenPauseMenu()
{
	AUserController* userController = Cast<AUserController>(GetController());
	if (!bPauseMenuOpened) {
		bPauseMenuOpened = true;
		userController->bShowMouseCursor = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		bPauseMenuOpened = false;
		userController->bShowMouseCursor = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

//GameInstance에 모든 정보 저장
void AUserPlayer::PackagePlayerData()
{
	//gameInstance->SetSavedInfo(InventoryComponent);
}