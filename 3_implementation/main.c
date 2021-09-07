#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//functions to generate bills
struct items{
    char item[20];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
void generatedBillHeader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t         SHINE Restaurant          ");
    printf("\n----------------------------------------");
    printf("\n Date:%s",date);
    printf("\nInvoice To:%s",name);
    printf("\n");
    printf("--------------------------------------\n");
    printf("Items \t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-------------------------------------");
    printf("\n\n");
}
void generatedBillBody(char item[30],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}
void generatedBillFooter(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.025*netTotal,grandTotal=netTotal+2*cgst;
    printf("---------------------------------\n");
    printf("subTotal\t\t\t%.2f",total);
    printf("\nDiscount@10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t-------------------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @2.5%s\t\t\t%.2f","%",cgst);
    printf("\n SGST @2.5%s\t\t\t%.2f","%",cgst);
    printf("\n------------------------------------");
    printf("\n Grand Total\t\t\t%.2f",grandTotal);
    printf("\n-------------------------------------\n");
}
int main(){
    float total;
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill='y',contFlag='y';
    char name[50];
    FILE *fp;
    while (contFlag=='y'){
        system ("clear");
        float total=0;
        int invoiceFound=0;
        printf("\t ------------ SHINE Restaurant -----------");
        printf("\n\n please select your prefered operation:\t");
        printf("\n\n1.Generate invoice");
        printf("\n2.Show all invoices");
        printf("\n3.Search invoice");
        printf("\n4.Exit");
        printf("\n\nyour choice:\t");
        scanf("%d",&opt);
        fgetc(stdin);
        switch(opt){
            case 1:
            system("clear");
            printf("\nplease enter the name of the customer:\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1]=0;
            strcpy(ord.date,__DATE__);
            printf("\nplease enter the number of items:\t");
            scanf("%d",&n);
            ord.numOfItems=n;
            for(int i=0;i<n;i++){
                fgetc(stdin);
                printf("\n\n");
                printf("please enter the item %d:\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("\n please enter the quntity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("\n please enter the unit price:\t");
                scanf("%f",&ord.itm[i].price);
                total +=ord.itm[i].qty * ord.itm[i].price;
            }
            generatedBillHeader(ord.customer,ord.date);
            for(int i=0;i<ord.numOfItems;i++){
                generatedBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generatedBillFooter(total);
            printf("\nDo you want to save the invoice:\t");
            scanf("%s",&saveBill);
            if(saveBill=='y'){
                fp=fopen("RestaurantBill.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite!=0)
                printf("\n sucessfully saved");
                else
                printf("error saving");
                fclose(fp);
            }
            break;
            case 2:
            system("clear");
            fp=fopen("RestaurantBill.dat","r");
            printf("\n*****previous invoices*****\n");
            while(fread(&order,sizeof(struct orders),1,fp)){
                float tot=0;
                generatedBillHeader(order.customer,order.date);
                for(int i=0;i<ord.numOfItems;i++){
                    generatedBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot +=order.itm[i].qty*order.itm[i].price;
                }
                generatedBillFooter(tot);
            }
            fclose(fp);
            break;
            case 3:
            printf("\n enter  the nae of customer:\t");
            fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            system("clear");
            fp=fopen("RestaurantBill.dat","r");
            printf("\t*****invoice of%s*****=\n",name);
            while(fread(&order,sizeof(struct orders),1,fp)){
                float tot=0;
                if(!strcmp(order.customer,name)){
                generatedBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++){
                    generatedBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot +=order.itm[i].qty*order.itm[i].price;
                }
                generatedBillFooter(tot);
                invoiceFound=1;
                }
        }
        if(!invoiceFound){
            printf("sorry the invoice for %s does not exist",name);
        }
        fclose(fp);
        break;
        case 4:
        printf("\n\t\tBye Bye:\n\n");
        exit(0);
        break;
        default:
        printf("sorry invalid option");
        break;
    }
    printf("\n do you want to perform another operation?[y/n}:\t");
    scanf("%s",&contFlag);
}
printf("\n\n");
return 0;
}
