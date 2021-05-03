// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerBody_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UPlayerBody_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerBody_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
	float PlayerSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
	bool IsAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
	float DirMove = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
	float DirForward = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
	float DirRight = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
	float AimDirRight = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
	float AimDirForward = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
	float Upper_Pitch = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
	float Upper_Yaw = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
	float Upper_Yaw2 = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	UClass* StateUpperNClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	UClass* StateDownNClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	UClass* StateUpperBClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	UClass* StateDownBClass = nullptr;
	



};