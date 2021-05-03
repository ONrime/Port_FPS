// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "MultiPlayer_CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API AMultiPlayer_CharacterBase : public APlayer_CharacterBase
{
	GENERATED_BODY()

public:
	AMultiPlayer_CharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
	class USkeletalMeshComponent* BodyMesh;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
		class USkeletalMeshComponent* GunMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
		class USkeletalMeshComponent* BodyMesh;*/

protected:
	virtual void BeginPlay() override;
	virtual void TurnAtRate(float Rate) override;
	virtual void LookUpAtRate(float Rate) override;
	virtual void PlayerJump() override;
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;

	/*UPROPERTY(Replicated)
	float Upper_Pitch = 0.0f;
	UPROPERTY(Replicated)
	float Upper_Yaw = 0.0f;
	UPROPERTY(Replicated)
	float Upper_Yaw2 = 0.0f; // 하체고정시 상체 회전 값 yaw2는 90도 정제 없이 180도 기준으로 출력*/

	//UPROPERTY(Replicated)
	//float Upper_Pitch2 = 0.0f;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Update_PitchAndYaw(float Pitch, float Yawm, float Yaw2);
	bool Server_Update_PitchAndYaw_Validate(float Pitch, float Yawm, float Yaw2);
	void Server_Update_PitchAndYaw_Implementation(float Pitch, float Yawm, float Yaw2);

	UPROPERTY(Replicated)
	float testd = 0.0f;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	// Base
	/*float GetUpper_Pitch() { return Upper_Pitch; }
	float GetUpper_Yaw() { return Upper_Yaw; } float GetUpper_Yaw2() { return Upper_Yaw2; }*/

private:
	void PitchAndYaw();
	
};
