// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNIT51_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ShootP(); //Function to fire projectile
	FTimerHandle DelayAttack; //Fire rate of projectile
	void RespawnP(); //Function called after delay(Fire rate)

public:	
	void DestroyEffect();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere, Category="Components")
		class UStaticMeshComponent* MyMesh;
	
	UPROPERTY(EditAnywhere, Category = "Components")
		class UProjectileMovementComponent* BulletMotion;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Components")
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Movement Speed")
		float speed=50.0f;

	UPROPERTY(EditAnywhere, Category = "Health")
		int health = 100;

	UPROPERTY(EditAnywhere, Category = "FireRate")
		float FireRate = 1 / 2.f;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UParticleSystem* DestroyEffectParticle;

	UPROPERTY(EditAnywhere, Category = "Components")
		USoundBase* DestroySound;

	float RunningTime;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AUnit51Projectile> ProjectileClass;

};
