
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

/*
	Compile/Exec Instructions
	*************************

	To compile:
		gcc -Wall -o lab6  myron_lab6.c

	To run:
		./lab6

*/


#define LINESIZE 1024

struct listing {
	int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count,availability_365;
	char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
	float latitude, longitude, price;
};



struct listing getfields(char	*line){
	struct listing item;

	/* Tokenize */

	item.id = atoi(strtok(line, ","));
	item.host_id = atoi(strtok(NULL, ","));
	item.host_name = strdup(strtok(NULL, ","));
	item.neighbourhood_group = strdup(strtok(NULL, ","));
	item.neighbourhood = strdup(strtok(NULL, ","));
	item.latitude = atof(strtok(NULL, ","));
	item.longitude = atof(strtok(NULL, ","));
	item.room_type = strdup(strtok(NULL, ","));
	item.price = atof(strtok(NULL, ","));
	item.minimum_nights = atoi(strtok(NULL, ","));
	item.number_of_reviews = atoi(strtok(NULL, ","));
	item.calculated_host_listings_count = atoi(strtok(NULL, ","));
	item.availability_365 = atoi(strtok(NULL, ","));

	return item;
}

/* display the struct */
void displayStruct(struct listing item, FILE *fp) {
	fprintf(fp, "ID : %d\n", item.id);
	fprintf(fp, "Host ID : %d\n", item.host_id);
	fprintf(fp, "Host Name : %s\n", item.host_name);
	fprintf(fp, "Neighbourhood Group : %s\n", item.neighbourhood_group);
	fprintf(fp, "Neighbourhood : %s\n", item.neighbourhood);
	fprintf(fp, "Latitude : %f\n", item.latitude);
	fprintf(fp, "Longitude : %f\n", item.longitude);
	fprintf(fp, "Room Type : %s\n", item.room_type);
	fprintf(fp, "Price : %f\n", item.price);
	fprintf(fp, "Minimum Nights : %d\n", item.minimum_nights);
	fprintf(fp, "Number of Reviews : %d\n", item.number_of_reviews);
	fprintf(fp,"Calculated Host Listings Count : %d\n", item.calculated_host_listings_count);
	fprintf(fp,"Availability_365 : %d\n\n", item.availability_365);
}

/*  comparison function for host_name field   */

    static int cmp_host_name(const void  *l1, const  void *l2){

	 struct listing *listing1 = (struct listing * ) l1;
 	 struct listing  *listing2 = (struct listing * ) l2;
	return strcmp(listing1 -> host_name, listing2 -> host_name);

}

/* comparison function for price field */
static int cmp_price(const void  *l1, const  void *l2){

         struct listing *listing1 = (struct listing * ) l1;
         struct listing  *listing2 = (struct listing * ) l2;

	 if (listing1 -> price < listing2 -> price)
		return -1;
	 else if (listing1 -> price > listing2 -> price)
		return 1;
	 else
		return 0;
}



int main(int argc, char *argv[]) {

	FILE *fp1, *fp2, *fp3;

	if (argc > 1){
		printf("\nUsage: %s\n", argv[0]);
	}

	/* Open 1 file for reading and 2 for writing  */
	if ((fp1 = fopen("listings.csv", "r")) == NULL) {
		printf("\n%s\n", "Error opening file for reading...");
		exit(-1);
	}
	fp2 = fopen("host_name.txt", "w");
	fp3 = fopen("price.txt", "w");

	struct listing list_items[22555];
	char line[LINESIZE];
	int i, count;


	count = 0;

	      /* read input till end of file and store it */
	while (fgets(line, LINESIZE, fp1) != NULL){
		list_items[count++] = getfields(line);
	}

	/* sort by host name field */

	qsort(list_items, count, sizeof(struct listing), cmp_host_name);

	fprintf(fp2,"\n%s\n", "**************************");
	fprintf(fp2,"\n%s\n", "Sorted by host name: \n");
	fprintf(fp2, "\n%s\n", "**************************\n");

	/* loop over list and call function that will write content to file */
        for (i=0; i<count; i++)
                displayStruct(list_items[i], fp2);

	/* Close file that was opened for reading */
	fclose(fp1);

	 /* sort by price field */

	 qsort(list_items, count, sizeof(struct listing), cmp_price);

	 fprintf(fp3,"\n%s\n", "**************************");
	 fprintf(fp3,"\n%s\n", "Sorted by price: \n");
	 fprintf(fp3,"\n%s\n", "**************************\n");

	/* loop over list and call function that will write content to file */
	for (i=0; i<count; i++)
		displayStruct(list_items[i], fp3);

	/* Close files that were opened for writing */
	fclose(fp2);
	fclose(fp3);
	return 0;
}
