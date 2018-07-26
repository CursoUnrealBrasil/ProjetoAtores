// Fill out your copyright notice in the Description page of Project Settings.

//Includes necess�rios para utilizar diversos recursos e classes no c�digo
// Indica ao Compilador onde ele via encontrar as fun��es e classes utilizadas
//E no momento da Linkedica��o ele vai colocar o c�digo relativo a estas fun��es e classes
#include "MeuGameMode.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Granada.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


void AMeuGameMode::StartPlay()
{
	Super::StartPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Estou no Game Mode \n Granadas Lancadas!"));
}


//Game mode � uma classe que cont�m as regras e configura��es do nosso jogo
// Cada level pode ter seu pr�prio game mode
// Para isso em World Settings voc� pode s1obrescrever o gamemode padr�o pelo seu gamemode
// Caso deseje substituir o gamemode para todos os levels use Edit->Project Settings
void AMeuGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Aqui declara uma variavel de nome LocalGranadas do tipo array din�mico capaz
	//de armazenar ponteiros(Endere�os de mem�ria) do tipo AActor ou subclasses de AActor
	TArray<AActor*> LocalGranadas;
	//A fun��o vai percorrer o mundo em busca de TargetPoints e cada Objeto deste tipo encontrado
	//Ir� adicionar no array din�mico LocalGranadas o endere�o de mem�ria de cada Target Point
	//No nosso caso ser�o coletados 7 endere�os e mem�ria e armazenados neste TArray LocalGranadas
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), LocalGranadas);
	//UE_LOG(LogTemp, Warning, TEXT("Num de Target Point Encontrados %d"), LocalGranadas.Num());
	if (LocalGranadas.Num() != 0)
	{
		//FActorSpawnParemets s�o configura��es que voc� pode criar adicionalmente para quando
		// Criar um ator atrav�s da fun��o SpawnActor
		// Contudo na maoria das vezes ser� apenas necess�rio os valores padr�o
		//Assim criamos uma vari�vel params e iniciamos ela com valores padr�o atrav�s
		// do resultado da chamda do construtor de FActorSapwnParamets
		FActorSpawnParameters params = FActorSpawnParameters();
		//Vai Iterar(Percorrer o TArray LocalGRanadas e a cada passada pelos �ndices de 0 a 6
		//pois s�o 7 elementos o comando for vai colocando dentro da vari�vel It o endere�o de mem�ria
		//de cada posi��o do Array din�mico LocalGranadas
		// Assim It � um iterador algo como um cursor que vai est� apontando para o array
		// Ent�o It cont�m um endere�o de mem�ria e desta forma ele � um PONTEIRO
		//Para encontrar e verificar o conte�do que It est� apontando fazemos (*it).GetActorLocation()
		// PAra simplicar usamos a nota��o flecha it->GetActorLocation();
		//Podemos ler assim: It v� l� no endere�o de mem�ria que voc� est� apontando e me diga
		// a localiza��o deste local...
		int32 i = 0;
		for (auto It : LocalGranadas) {
			GetWorld()->SpawnActor<AGranada>(It->GetActorLocation(), It->GetActorRotation(), params);
			//UE_LOG(LogTemp, Warning, TEXT("O que esta contido: %p em LocalGranda no Indice %d"), It, i++);
			//GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Ator Gerado"));
			//UE_LOG(LogTemp, Warning, TEXT("Transform = %s"), *It->GetActorLocation().ToString())

		}

	
	}
}





