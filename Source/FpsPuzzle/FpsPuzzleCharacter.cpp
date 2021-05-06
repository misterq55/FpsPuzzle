// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsPuzzleCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

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
	

	CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CHAR_MESH"));
	CharMesh->SetRelativeLocation(FVector(-5.5f, -4.4f, -165.7f));
	CharMesh->SetRelativeRotation(FRotator(0, -90.f, 0));
	CharMesh->SetupAttachment(Camera);

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ARM(TEXT("SkeletalMesh'/Game/first-person-arms/source/fpsarms.fpsarms'"));
	// SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CHAR(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));

	if (SK_CHAR.Succeeded())
	{
		CharMesh->SetSkeletalMesh(SK_CHAR.Object);
	}
}

// Called when the game starts or when spawned
void AFpsPuzzleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

