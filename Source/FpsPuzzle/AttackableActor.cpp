// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackableActor.h"
#include "InversionComponent.h"

// Sets default values
AAttackableActor::AAttackableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InversionComponent = CreateDefaultSubobject<UInversionComponent>(TEXT("InversionComponent"));
}

// Called when the game starts or when spawned
void AAttackableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

