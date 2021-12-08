// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


UCLASS()
class PAPI_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HorizontalMove(float value);
	void VerticalMove(float value);
	void HorizontalRot(float value);
	void VertialRot(float Value);

	void CheckJump();

	UPROPERTY()
		bool jumping;

	UPROPERTY()
		UCameraComponent*cam;
	UPROPERTY()
		USpringArmComponent* arm;
	
	UFUNCTION()
		void DoubleJump();

	UPROPERTY()
		int DoubleJumpCounter;

	UPROPERTY(EditAnywhere)
		float JumpHeight;

	UFUNCTION()
		void Dash();

	UPROPERTY(EditAnywhere)
		float DashDistance;

	UPROPERTY(EditAnywhere)
		float DashCooldown;

	UPROPERTY()
		bool CanDash;
	UPROPERTY(EditAnywhere)
		float DashStop;

	UPROPERTY()
		FTimerHandle UnusedHandle;
	
	UFUNCTION()
		void StopDashing();
	UFUNCTION()
		void ResetDash();
};
