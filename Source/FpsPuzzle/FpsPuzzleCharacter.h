// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsPuzzleCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class AWeaponActor;

UCLASS()
class FPSPUZZLE_API AFpsPuzzleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFpsPuzzleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);

	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

public:
	void SetWeapon(AWeaponActor* InWeaponActor);
	void Attack();

private:
	void Shot();

private:
	AWeaponActor* WeaponActor;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
};
