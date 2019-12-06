// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaTimeSlowAbility.h"
#include "Projectiles/Area.h"
#include "Triggers/DamageTrap.h"
#include "TopDownARPG.h"
#include "Engine/World.h"

void UAreaTimeSlowAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate IsValid(World) == false"));
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Source;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Source->GetActorLocation() + Source->GetActorForwardVector() * 300.0f;

	AActor* Projectile = World->SpawnActor<AActor>(AreaClass, SpawnLocation, Source->GetActorRotation(), SpawnParameters);
	if (IsValid(Projectile) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate IsValid(Area) == false"));
		return;
	}
}
