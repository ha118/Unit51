// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Unit51Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementcomponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a mesh and set it as root
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");
	SetRootComponent(MyMesh);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	ShootP();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Sin function used for movement of enemy
	FVector Location = GetActorLocation();
	float DeltaMt = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	Location.Y += DeltaMt * speed;
	RunningTime += DeltaTime;
	SetActorLocation(Location);
}

void AMyActor::ShootP()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			
			const FRotator SpawnRotation = GetActorRotation();
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AUnit51Projectile>(ProjectileClass, GetActorLocation() + FVector(50.f,0.f,50.f), SpawnRotation, ActorSpawnParams);
			GetWorld()->GetTimerManager().SetTimer(DelayAttack, this, &AMyActor::RespawnP, FireRate, false);
		}
	}
}

void AMyActor::RespawnP()
{
	ShootP();
}

void AMyActor::DestroyEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffectParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation());
	Destroy();
}
