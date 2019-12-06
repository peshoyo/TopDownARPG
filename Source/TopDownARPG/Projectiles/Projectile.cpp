// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "TopDownARPGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TopDownARPG.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);

	HelperSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Helper Sphere Component"));
	HelperSphere->InitSphereRadius(300.0f);
	HelperSphere->SetCollisionProfileName(TEXT("Trigger"));
	HelperSphere->SetupAttachment(RootComponent);

	HelperSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	HelperSphere->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);

	OnOverlapParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	OnOverlapParticle->bAutoActivate = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OnOverlapParticle))
	{
		OnOverlapParticle->ActivateSystem();
	}

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		Character->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
		
	}
		if (Destroy() == false)
		{
			UE_LOG(LogTopDownARPG, Error, TEXT("Projectile is indestructable"));
		}
}
void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTopDownARPG, Display, TEXT("AProjectile::Overlap"));

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		Character->ChangeDamage(DamageOverTime);
	}

}
void AProjectile::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTopDownARPG, Display, TEXT("AProjectile::OverlapEnd"));

	ATopDownARPGCharacter* Character = Cast<ATopDownARPGCharacter>(OtherActor);
	if (IsValid(Character))
	{
		Character->ChangeDamage(0.0);
	}
	
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

