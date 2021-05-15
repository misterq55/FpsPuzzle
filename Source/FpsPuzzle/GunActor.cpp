// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"

AGunActor::AGunActor()
	: AWeaponActor()
	, GunMuzzle(FVector::ZeroVector)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));

	if (SK_WEAPON.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(SK_WEAPON.Object);

		GunMuzzle = FVector(0.f, -10.578201f, 59.460724f);
	}
}