// Fill out your copyright notice in the Description page of Project Settings.


#include "Area.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "TopDownARPGCharacter.h"
#include "TopDownARPG.h"
#include "Projectile.h"

// Sets default values
AArea::AArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Helper Sphere Component"));
	AreaSphere->InitSphereRadius(300.0f);
	AreaSphere->SetCollisionProfileName(TEXT("Trigger"));
	AreaSphere->SetupAttachment(RootComponent);

	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AArea::OnOverlapBegin);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AArea::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AArea::BeginPlay()
{
	Super::BeginPlay();
	FVector ActorLocation = GetActorLocation();
	DrawDebugSphere(GetWorld(), ActorLocation, 400.f, 50, FColor::Cyan, true, -1, 0, 2);
	
}
void AArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTopDownARPG, Display, TEXT("AArea::Overlap"));

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		Character->ChangeDamage(DamageOverTime);
		Character->CustomTimeDilation = 0.2;
	}
	AProjectile* Projectile = Cast<AProjectile>(Other);
	if (Projectile) {
		Projectile->CustomTimeDilation = 0.2;
	}
}
void AArea::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTopDownARPG, Display, TEXT("AArea::OverlapEnd"));
	

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(OtherActor);
	if (IsValid(Character))
	{
		Character->ChangeDamage(0.0);
		Character->CustomTimeDilation = 1;
	}

	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (Projectile) {
		Projectile->CustomTimeDilation = 1;
	}
}
// Called every frame
void AArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

