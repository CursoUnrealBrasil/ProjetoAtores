// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InserirGranadas.generated.h"

UCLASS()
class PROJATORES_API AInserirGranadas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInserirGranadas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class USphereComponent* ColisorDoAtor;
	
	//Propriedade vis�vel no editor que vai permitir indicar qual a classe
	//que o objeto pertence
	//Contudo a escolha desta classe ser� limitada por TSubclassof (Subclasse de)
	//Ou seja neste caso estamos indicando que s� ser� permitido escolher no editor
	//A classe Granada ou suas subclasses
	UPROPERTY(EditAnywhere, Category = "Tipo Granada")
	TSubclassOf<class AGranada> BpGranada;
	
	
};
