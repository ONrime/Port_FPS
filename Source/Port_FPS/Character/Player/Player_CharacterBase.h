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
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void PlayerJump();
	virtual void PlayerCrouch();
	void Move(float DeltaSeconds);

	UPROPERTY(Replicated)
	float Upper_Pitch = 0.0f;
	UPROPERTY(Replicated)
	float Upper_Yaw = 0.0f;
	UPROPERTY(Replicated)
	float Upper_Yaw2 = 0.0f; // 하체고정시 상체 회전 값 yaw2는 90도 정제 없이 180도 기준으로 출력
	float AimDirRight = 0.0f, AimDirForward = 0.0f; // 컨트롤러로 부터 받은 시점 키값 (AnimBP에서 사용하기 위해)
	float InputDirForward = 0.0f;
	float InputDirRight = 0.0f; // 컨트롤러로 부터 받은 이동 키값 (AnimBP에서 사용하기 위해)
	FVector MoveDir = FVector::ZeroVector;
	float InputDir = 0.0f;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	FVector DirMoveForwerd = FVector::ZeroVector;
	// Base
	float GetUpper_Pitch() { return Upper_Pitch; }
	float GetUpper_Yaw() { return Upper_Yaw; } float GetUpper_Yaw2() { return Upper_Yaw2; }
	float GetAimDirRight() { return AimDirRight; } float GetAimDirForward() { return AimDirForward; }
	float GetInputDirForward() { return InputDirForward; } float GetInputDirRight() { return InputDirRight; }
	FVector GetHeadCameraLoc() { return HeadCameraLoc; } void SetHeadCameraLoc(FVector set) { HeadCameraLoc = set; }
	bool IsMove = true;
	bool IsPlayerCameraTurn = true;
	bool IsPlayerRotationYawSpeedSlow = false;

	class UPlayerUpper_StateBase* GetStateUpperN() { return StateUpperN; }
	class UPlayerDown_StateBase* GetStateDownN() { return StateDownN; }
	void SetStateUpperN(class UPlayerUpper_StateBase* state);
	void SetStateDownN(class UPlayerDown_StateBase* state);
	UClass* StateUpperBClass = nullptr; UClass* StateDownBClass = nullptr;   //전 상태에 대한 Class값 (AnimBP에서 사용하기 위해)
	UClass* StateUpperNClass = nullptr; UClass* StateDownNClass = nullptr;   //전 상태에 대한 Class값 (AnimBP에서 사용하기 위해)
	void UpperPress(class UPlayerUpper_StateBase* state);
	void DownPress(class UPlayerDown_StateBase* state);

private:
	FVector HeadCameraLoc = FVector::ZeroVector;
	

	class UPlayerDown_StateBase* StateDownN = nullptr;
	class UPlayerUpper_StateBase* StateUpperN = nullptr;

};
