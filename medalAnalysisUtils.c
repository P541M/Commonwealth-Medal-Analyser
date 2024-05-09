#include "functionHeaders.h"

/*Function Definition 1
Reads data from the file and populates arrays.*/
void readFromFile(char fName[30], int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    int i = 0;
    FILE* filePointer;
    filePointer = fopen(fName, "r");

    // Gets the country and their 3 medal categories
    while (!feof(filePointer)) {
        fscanf(filePointer, "%s %d %d %d", countryNames[i], &country[i][0], &country[i][1], &country[i][2]);
        i++;
    }
    fclose(filePointer);
}

/*Function Definition 2
Finds total medals per country.*/
void findTotalPerCountry(int country[COUNTRIES][MEDALCAT], int totalAllCountries[COUNTRIES]) {
    // Adds up all medal categories for the country
    for (int i = 0; i < COUNTRIES; i++) {
        totalAllCountries[i] = country[i][0] + country[i][1] + country[i][2];
    }
}

/*Function Definition 3
Finds total medals per category and maximum category.*/
int findTotalPerMedal(int country[COUNTRIES][MEDALCAT], int totalAllMedals[MEDALCAT], int* whichMedal) {
    for (int i = 0; i < MEDALCAT; i++) {
        totalAllMedals[i] = 0;
        for (int j = 0; j < COUNTRIES; j++) {
            totalAllMedals[i] += country[j][i];
        }
    }

    int max = totalAllMedals[0];
    *whichMedal = 0;
    for (int i = 1; i < MEDALCAT; i++) {
        if (totalAllMedals[i] > max) {
            max = totalAllMedals[i];
            *whichMedal = i;
        }
    }

    return max;
}

/*Function Definition 4
Displays a histogram of medals.*/
void hHistogram(char countryNames[COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]) {
    int i = 0;
    int j = 0;
    int w = 0;
    int numOfStars = 0;

    printf("\n");
    while (i < COUNTRIES) {
        if (totalMedals[i] % 2 == 0) {
            numOfStars = (totalMedals[i] / 2);
        } else if (totalMedals[i] % 2 == 1) {
            numOfStars = (totalMedals[i] / 2) + 1;
        }

        printf("%s", countryNames[i]);
        while (w < 10 - strlen(countryNames[i])) {
            printf(" ");
            w++;
        }
        w = 0;

        printf(":");
        while (j < numOfStars) {
            printf("*");
            j++;
        }
        j = 0;

        printf(" (%d)\n", totalMedals[i]);

        i++;
    }
}

/*Function Definition 5
Searches for a country and returns total medals.*/
int searchCountry(char countryName[MAX_LENGTH_CNAME], char countryNames[COUNTRIES][MAX_LENGTH_CNAME],
                  int totalAllCountries[COUNTRIES]) {
    int i = 0;

    while (i < COUNTRIES) {
        if (strcmp(countryName, countryNames[i]) == 0) {
            return totalAllCountries[i];
        }
        i++;
    }
    return -1;
}

/*Function Definition 6
Ranks top three countries by total medals.*/
void rankTopThreeByTotal(int totalAllCountries[COUNTRIES], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    int indices[COUNTRIES];
    for (int i = 0; i < COUNTRIES; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < COUNTRIES - 1; i++) {
        for (int j = i + 1; j < COUNTRIES; j++) {
            if (totalAllCountries[indices[i]] < totalAllCountries[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Prints the final results
    printf("Top 3 medal countries\n");
    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", countryNames[indices[i]], totalAllCountries[indices[i]]);
    }
}

/*Function Definition 7
Ranks top three countries by gold medals.*/
void rankTopThreeByMedal(int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    int indices[COUNTRIES];
    for (int i = 0; i < COUNTRIES; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < COUNTRIES - 1; i++) {
        for (int j = i + 1; j < COUNTRIES; j++) {
            if (country[indices[i]][0] < country[indices[j]][0]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Prints the final results
    printf("Top 3 gold countries\n");
    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", countryNames[indices[i]], country[indices[i]][0]);
    }
}

/*Function Definition 8
Finds countries with no medals of a specific category.*/
int findAllWithNoXMedals(int country[COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries[COUNTRIES]) {
    int count = 0;
    for (int i = 0; i < COUNTRIES; i++) {
        if (country[i][indexMedal] == 0) {
            indexOfCountries[count++] = i;
        }
    }
    return count;
}

/*Function Definition 9
Finds countries with only medals of a specific category.*/
int findAllWithOnlyXMedals(int country[COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries[COUNTRIES]) {
    int count = 0;
    for (int i = 0; i < COUNTRIES; i++) {
        if (country[i][indexMedal] > 0 && country[i][(indexMedal + 1) % MEDALCAT] == 0 &&
            country[i][(indexMedal + 2) % MEDALCAT] == 0) {
            indexOfCountries[count++] = i;
        }
    }
    return count;
}

/*Function Definition 10
Finds the index of the country with min or max length name.*/
int findCountryIndexWithMinOrMaxLength(int minOrMax, char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    int index = 0;
    if (minOrMax == 1) {  // find min length
        int minLength = strlen(countryNames[0]);
        for (int i = 1; i < COUNTRIES; i++) {
            int len = strlen(countryNames[i]);
            if (len < minLength) {
                minLength = len;
                index = i;
            }
        }
    } else if (minOrMax == 2) {  // find max length
        int maxLength = strlen(countryNames[0]);
        for (int i = 1; i < COUNTRIES; i++) {
            int len = strlen(countryNames[i]);
            if (len > maxLength) {
                maxLength = len;
                index = i;
            }
        }
    }
    return index;
}
