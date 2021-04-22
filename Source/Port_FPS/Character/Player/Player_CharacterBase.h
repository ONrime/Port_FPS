// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/CharacterBase.h"
#include "Player_CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API APlayer_CharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	APlayer_CharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
	class USkeletalMeshComponent* ArmMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBase)
	float PlayerSpeed = 70.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate = 45.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate = 45.0f;

protected:
	virtual void BeginPlay() override;
	virtual void TurnAtRate(float Rate);
	virtual void LookUpAtRate(float Rate);
	virtual void PlayerJump();
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	float Upper_Pitch = 0.0f, Upper_Yaw = 0.0f, Upper_Yaw2 = 0.0f; // ��ü������ ��ü ȸ�� �� yaw2�� 90�� ���� ���� 180�� �������� ���
	float AimDirRight = 0.0f, AimDirForward = 0.0f; // ��Ʈ�ѷ��� ���� ���� ���� Ű�� (AnimBP���� ����ϱ� ����)
	float InputDirForward = 0.0f, InputDirRight = 0.0f; // ��Ʈ�ѷ��� ���� ���� �̵� Ű�� (AnimBP���� ����ϱ� ����)

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	// Base
	float GetUpper_Pitch() { return Upper_Pitch; };
	float GetUpper_Yaw() { return Upper_Yaw; }; float GetUpper_Yaw2() { return Upper_Yaw2; };
	float GetAimDirRight() { return AimDirRight; }; float GetAimDirForward() { return AimDirForward; };
	float GetInputDirForward() { return InputDirForward; }; float GetInputDirRight() { return InputDirRight; };
	bool IsMove = true;
	bool IsPlayerCameraTurn = true;

private:
	void Move(float DeltaSeconds);
	FVector MoveDir = FVector::ZeroVector;


};
