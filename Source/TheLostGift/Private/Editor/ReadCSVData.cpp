// Copyright © 2023 FireTaleStudio.

#include "Editor/ReadCSVData.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

void UReadCSVData::ReadCSVFile(const FString& DownloadURL, const int32& DataSheetID)
{
	const FString URL = DownloadURL + FString::FromInt(DataSheetID);
	UE_LOG(LogTemp, Error, TEXT("%s"), *URL);
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(URL);
	Request->SetVerb("GET");

	Request->OnProcessRequestComplete().Unbind();
	Request->OnProcessRequestComplete().BindUObject(this, &UReadCSVData::OnDownloadComplete);

	Request->ProcessRequest();
}

void UReadCSVData::OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bWasSuccessful)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Response->GetContentType());
	if (bWasSuccessful && Response.IsValid() && Response->GetContentType() == "text/csv")
	{
		const FString CSVData = Response->GetContentAsString();
		const TArray<FString> CSVLines = ParseCSVDataIntoLines(CSVData);
		
		OnCSVDownloaded.Broadcast(CSVLines);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Failed to download Google Sheet as CSV."));
}

// A function to parse CSV data into lines
TArray<FString> UReadCSVData::ParseCSVDataIntoLines(const FString& CSVData)
{
	TArray<FString> CSVLines;
	CSVData.ParseIntoArrayLines(CSVLines);
	
	return CSVLines;
}

// A function to parse a CSV line into columns
TArray<FString> UReadCSVData::ParseCSVLineIntoColumns(const FString& CSVLine)
{
	TArray<FString> CSVColumns;
	CSVLine.ParseIntoArray(CSVColumns, TEXT(","), true);

	return CSVColumns;
}