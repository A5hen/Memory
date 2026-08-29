// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplanationSet.h"

const FText* UExplanationSet::GetExplanation(const FName& ExplanationID) const
{
    return Explanations.Find(ExplanationID);
}
