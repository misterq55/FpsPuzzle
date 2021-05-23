// Fill out your copyright notice in the Description page of Project Settings.


#include "InversionActor.h"
#include "InversionComponent.h"

// Sets default values
AInversionActor::AInversionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InversionComponent = CreateDefaultSubobject<UInversionComponent>(TEXT("InversionComponent"));

}

// Called when the game starts or when spawned
void AInversionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInversionActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	GetMesh()->SetSimulatePhysics(true);
	SetIsInversed(true);
}

void AInversionActor::OnInversionActorHit(FVector ForwardVector)
{
	GetMesh()->SetSimulatePhysics(true);
	SetIsInversed(true);

	UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(GetMesh());
	SM->AddImpulse(ForwardVector * SM->GetMass() * 1500);
}

// Called every frame
void AInversionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

