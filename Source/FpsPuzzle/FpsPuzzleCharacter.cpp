// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsPuzzleCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GunActor.h"
#include "DrawDebugHelpers.h"
#include "InversionActor.h"

// Sets default values
AFpsPuzzleCharacter::AFpsPuzzleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// bUseControllerRotationPitch = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-34.56f, 1.75f, 74.f));
	Camera->bUsePawnControlRotation = true;
	

	// CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CHAR_MESH"));
	GetMesh()->SetRelativeLocation(FVector(-5.5f, -4.4f, -165.7f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));
	GetMesh()->SetupAttachment(Camera);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CHAR(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	if (SK_CHAR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CHAR.Object);
	}

}

// Called when the game starts or when spawned
void AFpsPuzzleCharacter::BeginPlay()
{
	Super::BeginPlay();;

	GetMesh()->HideBoneByName(TEXT("neck_01"), EPhysBodyOp::PBO_MAX);

	// 애니메이션 초기화
	// UAnimSequence *Anim = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("/Game/InfinityBladeWarriors/Character/Animations/Idle_Pistol.Idle_Pistol")));
	UAnimSequence* Anim = Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("AnimSequence'/Game/InfinityBladeWarriors/Character/Animations/Idle_Rifle_Ironsights.Idle_Rifle_Ironsights'")));

	if (Anim)
	{
		GetMesh()->PlayAnimation(Anim, false);
		GetMesh()->Stop();
	}

	// 무기 장착
	SetWeapon(GetWorld()->SpawnActor<AGunActor>());
}

// Called every frame
void AFpsPuzzleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFpsPuzzleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AFpsPuzzleCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFpsPuzzleCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFpsPuzzleCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFpsPuzzleCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFpsPuzzleCharacter::LookUp);
}

void AFpsPuzzleCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AFpsPuzzleCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

void AFpsPuzzleCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AFpsPuzzleCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AFpsPuzzleCharacter::SetWeapon(AWeaponActor* InWeaponActor)
{
	WeaponActor = InWeaponActor;

	USkeletalMeshComponent* WeaponMeshComponent = WeaponActor->GetWeaponMesh();

	if (WeaponMeshComponent)
	{
		WeaponMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("hand_rSocket")));
	}
}

void AFpsPuzzleCharacter::Attack()
{
	if (nullptr != WeaponActor)
	{
		Shot();
	}
}

void AFpsPuzzleCharacter::Shot()
{
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, this);

	float Radius = 5.f;
	float Range = 2000.f;

	FVector StartLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector ForwardVector = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();

	FVector ResultVector = StartLocation + ForwardVector * Range;

	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		StartLocation + ForwardVector * Range,
		ECollisionChannel::ECC_GameTraceChannel3,
		Params
	);

	FColor DrawColor = bResult ? FColor::Green : FColor::Red;

	/*UE_LOG(LogTemp, Warning, TEXT("Start : %f %f %f"), StartLocation.X, StartLocation.Y, StartLocation.Z);
	UE_LOG(LogTemp, Warning, TEXT("End : %f %f %f"), ResultVector.X, ResultVector.Y, ResultVector.Z);*/

	DrawDebugLine(
		GetWorld(),
		StartLocation + ForwardVector * 30.f,
		StartLocation + ForwardVector * Range,
		DrawColor,
		false,
		5.f,
		(uint8)'\000',
		5.f
	);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			AInversionActor* HitInversionActor = Cast<AInversionActor>(HitResult.Actor.Get());
			HitInversionActor->OnInversionActorHit(HitResult, ForwardVector);
		}
	}
}

