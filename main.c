#include <stdio.h>

#include "functionHeaders.h"

int main(int argc, char *argv[]) {

    int country[COUNTRIES][MEDALCAT];
    char countryNames[COUNTRIES][MAX_LENGTH_CNAME];
    int totalAllCountries[COUNTRIES];
    int totalAllMedals[MEDALCAT];
    int countrySearch;
    char countryName[MAX_LENGTH_CNAME];
    int medalChoice;
    int otherMedalChoice;
    int countryFound;
    int otherCountryFound;
    int countryIndex;
    int indexOfCountries[COUNTRIES];
    int totalMedal;
    int minOrMaxD;
    int choice;

    // call function readFromFile to populate your arrays
    readFromFile(argv[1], country, countryNames);

    do {
        printf("\nHere is the menu \n\n");
        printf("1. Display all country names and total medals\n");
        printf("2. Find total number of medals per country\n");
        printf("3. Find total number of medals per category\n");
        printf("4. Display horizontal histogram\n");
        printf("5. Search country and return total medals\n");
        printf("6. Rank top three countries by total medals\n");
        printf("7. Rank top three countries by gold medals\n");
        printf("8. Find countries with no medals of a specific category\n");
        printf("9. Find countries with only medals of a specific category\n");
        printf("10. Find country with min or max length name\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                printf("\nAll country names and their medals\n\n");
                readFromFile(argv[1], country, countryNames);

                // Goes through all 15 countries and prints the names and their medals
                for (int i = 0; i < COUNTRIES; i++) {
                    printf("%-11s ", countryNames[i]);
                    printf("Gold: %-3d, Silver: %-3d, Bronze: %-3d\n", country[i][0], country[i][1], country[i][2]);
                }

                break;
            case 2:

                printf("\nTotal medals won by all the countries\n\n");

                // Calls function
                findTotalPerCountry(country, totalAllCountries);

                // Goes through all 15 countries and prints their total medals
                for (int i = 0; i < COUNTRIES; i++) {
                    printf("%-11s: ", countryNames[i]);
                    printf("%d \n", totalAllCountries[i]);
                }

                break;
            case 3:

                readFromFile(argv[1], country, countryNames);
                int medal;
                totalMedal = findTotalPerMedal(country, totalAllMedals, &medal);

                // Prints the medals and their amounts
                printf("Medal: Gold, Total: %d\n", totalAllMedals[0]);

                printf("Medal: Silver, Total: %d\n", totalAllMedals[1]);

                printf("Medal: Bronze, Total: %d\n", totalAllMedals[2]);

                printf("Max num of medals: %d in ", totalMedal);

                // Prints the categories
                if (medal == 0) {
                    printf("Gold\n");
                } else if (medal == 1) {
                    printf("Silver\n");
                } else if (medal == 2) {
                    printf("Bronze\n");
                }

                break;
            case 4:

                // Function calls
                findTotalPerCountry(country, totalAllCountries);
                hHistogram(countryNames, totalAllCountries);

                break;
            case 5:

                // Gets input from user
                printf("Country: ");
                scanf(" %s", countryName);

                // Calls function
                findTotalPerCountry(country, totalAllCountries);
                countrySearch = searchCountry(countryName, countryNames, totalAllCountries);

                // Validation input
                if (countrySearch == -1) {
                    printf("Country name not valid\n");
                } else {
                    printf("%s has a total of %d medals", countryName, countrySearch);
                }

                break;
            case 6:

                // Function calls
                findTotalPerCountry(country, totalAllCountries);
                rankTopThreeByTotal(totalAllCountries, countryNames);

                break;
            case 7:

                // Function calls
                findTotalPerCountry(country, totalAllCountries);
                rankTopThreeByMedal(country, countryNames);

                break;
            case 8:

                // Input from user
                printf("Which medal would you want? 0, 1, 2 (Gold, Silver, Bronze): ");
                scanf("%d", &medalChoice);

                int j = 0;

                // Function calls
                countryFound = findAllWithNoXMedals(country, medalChoice, indexOfCountries);

                // Prints if the country won any medals
                while (j < countryFound) {
                    if (medalChoice == 0 || medalChoice == 1 || medalChoice == 2) {
                        printf("\n%s Country won no medals in the category", countryNames[indexOfCountries[j]]);
                    }

                    j++;
                }

                // Validation input
                if (countryFound == 0) {
                    printf("No countries found");
                }

                break;
            case 9:

                printf("Enter medal category (1 for Gold, 2 for Silver, 3 for Bronze): ");
                int onlyMedals[COUNTRIES];
                scanf("%d", &otherMedalChoice);
                otherCountryFound = findAllWithOnlyXMedals(country, otherMedalChoice - 1, onlyMedals);
                printf("Countries with only %s medals:\n", (otherMedalChoice == 1)   ? "Gold"
                                                           : (otherMedalChoice == 2) ? "Silver"
                                                                                     : "Bronze");
                for (int i = 0; i < otherCountryFound; i++) {
                    printf("%s\n", countryNames[onlyMedals[i]]);
                }

                if (otherCountryFound == 0) {
                    printf("No countries found");
                }

                break;
            case 10:

                // Gets input from user
                printf("Would you want to find the min or max? (1 or 2): ");
                scanf("%d", &minOrMaxD);

                // Function calls
                countryIndex = findCountryIndexWithMinOrMaxLength(minOrMaxD, countryNames);

                // Prints the country
                if (minOrMaxD == 1) {
                    printf("\nThis country has the min length: %s\n", countryNames[countryIndex]);
                }
                if (minOrMaxD == 2) {
                    printf("\nThis country has the max length: %s\n", countryNames[countryIndex]);
                }

                break;

            case 11:
                return 0;

            default:
                printf("That is an invalid choice\n");
        }

    } while (choice != 11);

    return 0;
}
