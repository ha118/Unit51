// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unit51Projectile.h"
#include "MyActor.h"
#include "Unit51Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

AUnit51Projectile::AUnit51Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUnit51Projectile::OnHit);// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AUnit51Projectile::OnOverlapBegin);// set up a notification for when this component overlaps something blocking
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	//Tracer
	//Tracer = CreateDefaultSubobject<UParticleSystem>("Tracer");
	//Tracer->AttachTo(RootComponent);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AUnit51Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 10.0f, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, GetActorLocation());
		Destroy();
	}
	else
	{
		if (OtherActor != nullptr)
		{
			//Cast to enemy and reduce health (For bullet shot by player)
			AMyActor* hitenemy = Cast<AMyActor>(OtherActor); 

			if (hitenemy != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
				hitenemy->health -= 20;
				if (hitenemy->health <= 0)
				{
						hitenemy->DestroyEffect();
						AUnit51Character* Player = Cast<AUnit51Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
						if (Player != NULL)
						{
							Player->increaseAmmo();
						}
				}
			}
			
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, GetActorLocation());
		Destroy();
	}
}

void AUnit51Projectile::OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor != nullptr)
	{
		//Cast to player character and reduce health (For Projectiles fired by enemy)
		AUnit51Character* Player = Cast<AUnit51Character>(OtherActor);
		if (Player != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
			Player->getHit();
			Destroy();
		}

		//Cast to this projectile and check if bullet fired by player hit a projectile fire by enemy.
		//If bullet hits a projectile, destroy projectile. No effect on bullet.
		AUnit51Projectile* EnemyProj = Cast<AUnit51Projectile>(OtherActor);
		if (EnemyProj != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
			//Player->getHit();
			EnemyProj->Destroy();
		}
		
	}
}

void AUnit51Projectile::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::SpawnEmitterAttached(Tracer, RootComponent);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, GetActorLocation(),GetActorRotation());
}