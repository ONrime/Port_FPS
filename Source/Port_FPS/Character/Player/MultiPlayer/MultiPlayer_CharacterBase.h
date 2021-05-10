// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "Net/UnrealNetwork.h"
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

	void PlayerInputTest();


protected:
	virtual void BeginPlay() override;
	virtual void TurnAtRate(float Rate) override;
	virtual void LookUpAtRate(float Rate) override;
	virtual void PlayerJump() override;
	virtual void PlayerCrouch() override;
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	


	//UPROPERTY(Replicated)
	//float Upper_Pitch2 = 0.0f;

	

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_Update_PlayerMove(FVector Dir, float DirInput);
	bool Server_Update_PlayerMove_Validate(FVector Dir, float DirInput);
	void Server_Update_PlayerMove_Implementation(FVector Dir, float Input);

	UFUNCTION(Server, WithValidation, Reliable)// ���������� ȣ��ǵ��� ����
	void Server_PlayerRotation(float PlayerRotationSpeed, float PlayerYaw);
	void Server_PlayerRotation_Implementation(float PlayerRotationSpeed, float PlayerYaw);
	bool Server_PlayerRotation_Validate(float PlayerRotationSpeed, float PlayerYaw);

	UFUNCTION(Reliable, Server, WithValidation)
	void Server_Update_PlayerDownState(UPlayerDown_StateBase* state);
	bool Server_Update_PlayerDownState_Validate(UPlayerDown_StateBase* state);
	void Server_Update_PlayerDownState_Implementation(UPlayerDown_StateBase* state);
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void Server_Update_PlayerUpperState(UPlayerUpper_StateBase* state);
	bool Server_Update_PlayerUpperState_Validate(UPlayerUpper_StateBase* state);
	void Server_Update_PlayerUpperState_Implementation(UPlayerUpper_StateBase* state);
	

	UPROPERTY(Replicated)
	float testd = 0.0f;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	// Base
	/*float GetUpper_Pitch() { return Upper_Pitch; }
	float GetUpper_Yaw() { return Upper_Yaw; } float GetUpper_Yaw2() { return Upper_Yaw2; }*/

	UPROPERTY(Replicated)
	float PlayerRotationYawSpeed = 0.0f;
	UPROPERTY(Replicated)
	float PlayerRotationYaw = 0.0f;

private:
	void PitchAndYaw();
	
};
