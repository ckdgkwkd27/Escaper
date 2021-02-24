 

#pragma once

#include "PlayerCharacter.h"
#include "PlayerAnim.h"
#include "Weapon.h"
#include "InventoryComponent.h"
#include "MainGameModeBase.h"
#include "PickupItem.h"
#include "GameFramework/Character.h"
#include "UserPlayer.generated.h"

UCLASS()
class ESCAPER_API AUserPlayer : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUserPlayer();
	void Fire();
	void SetWeapon();
	void GenerateWeapon(TSubclassOf<AWeapon> weapon);
	void ChangeAnim(EPlayerAnim anim);
	void ReloadBullet();
	void PackagePlayerData();

	UFUNCTION(BlueprintCallable)
	void SetHealth(int32 hp);

	UFUNCTION(BlueprintCallable)
	int32 GetHealth() {
		return iHP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHelath() {
		return iMAX_HP;
	}

	UFUNCTION(BlueprintCallable)
	UUIPlayerHUD* GetPlayerHUD() const {
		return playerHUD;
	}

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(UInventoryComponent* _inven) {
		InventoryComponent = _inven;
	}

	UFUNCTION(BlueprintCallable)
	AWeapon* GetWeapon() const {
		return Weapon;
	}

	UInventoryComponent* GetInventory() const {
		return InventoryComponent;
	}

	UUIEnding* GetEndingMenu() const {
		return EndingMenu;
	}

	TArray<AWeapon*> CollectedWeapons;

private:
	UPROPERTY()
	UEscaperGameInstance* gameInstance; // 게임 정보들 저장
	float fAttack_time;
	float fAttack_time_max;
	bool bAttackEnable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* Arm;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Cameras;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 iMAX_HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 iHP;

	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY()
	UUserWidget* Inventory;

	UPROPERTY()
	UUserWidget* DeathMenu;

	UPROPERTY()
	UUserWidget* PauseMenu;

	UPROPERTY()
	UUIEnding* EndingMenu;

	UPROPERTY()
	AMainGameModeBase* GameMode;

	UPROPERTY()
	class UUserAnim* UserAnim;

	UPROPERTY()
	class AWeapon* Weapon;

	UPROPERTY()
	UUIPlayerHUD* playerHUD;

	UPROPERTY()
	class APickupItem* pi;

	bool bIsPickupItem;
	bool bInventoryOpened;
	bool bPauseMenuOpened;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	void MoveFront(float fScale);
	void MoveSide(float fScale);
	void RotationZ(float fScale);
	void LookUp(float fScale);
	void JumpKey();
	void NormalAttack();
	void EndAttack();
	void Interact();
	void Reload();
	void Equip();
	void SelectWeapon();
	void OpenInventory();
	void OpenPauseMenu();
};
