#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
struct customer{
	char name[10];
	int mobileNo;
	char address[20];
};

struct login {
	char userid[10];
	char password[20];
};

struct product {
	char fname[10];
	int price;
	char category[10];	

};

void createAccountAdmin(){
	struct login admin;
	FILE *ptr;
	ptr=fopen("register.txt","w");
	
			fflush(stdin); 
		 printf("Enter the uid=");
		   gets(admin.userid);
		fflush(stdin); 
		 printf("Enter the password=");
		   gets(admin.password);
		fflush(stdin); 
		
		 fwrite(&admin,sizeof(admin),1,ptr);
		printf("\n Hey %s Now your are admin....",admin.userid);
}
int verifiedAdmin() {
	static int failed_attempts = 0; // keep across function calls
    static time_t block_start = 0;
    
    if (failed_attempts >= 3) {
        time_t current_time = time(NULL);
        if (difftime(current_time, block_start) < 60) {
            printf("Too many failed attempts. Please try again after 1 minute.");
            return 0;
        } else {
            // unblock after 1 min
            failed_attempts = 0;
        }
    }
	
			struct login admin;
		char x[10],y[10];
		int k1,k2;
		FILE *ptr;
		int found=0;
		ptr=fopen("register.txt","r");
		 fflush(stdin);
		 printf("\n Enter user id=");
		   gets(x);
		fflush(stdin);
		 printf("\n Enter user password=");
		   gets(y);
		   
		 
		fread(&admin,sizeof(admin),1,ptr);
			fclose(ptr);
	 
			 k1=strcmp(admin.userid,x);
			 if(k1==0)
			 {
			 	// id match
			 	k2=strcmp(admin.password,y);
			 	if(k2==0)
			 	{
			 		failed_attempts=0;
			 		return 1;	
				}
				else
				{
					printf("Wrong password");
					failed_attempts++;	
				}
			 }
			 else
			 {
				printf("Wrong user id:");
				failed_attempts++;	
			 }
			  if (failed_attempts>=3)
			     block_start=time(NULL);
			  
			  return 0;
			 
	
}
int check(int pno)	
	{
		
		struct customer r;
		FILE *ptr;
		int found=0;
		ptr=fopen("rec.txt","r");
		 
		while(fread(&r,sizeof(r),1,ptr))
		{
		   
			if(r.mobileNo==pno)
			{
				printf("\n hello");
				found=1;
				break;
			}
		}
		fclose(ptr);
	 
		if(found==1)
			return 1; // when exist
		else	
			return 0; // not found
		
		
	}
void createNewCustomer(){
	struct customer r;
	FILE *ptr;
	ptr=fopen("rec.txt","a");
	fflush(stdin);
	printf("Enter Your Name...");
	gets(r.name);
	
	fflush(stdin);
	printf("your mobile no...");
	scanf("%d",&r.mobileNo);
	
	fflush(stdin);
	printf("your address..");
	gets(r.address);
	int k;
	k=check(r.mobileNo);
	if(k==1){
			 printf("already exit this customer...");
		}
	else{
			fwrite(&r,sizeof(r),1,ptr);
			printf("\n Hey %s you are  register successfully....",r.name);
			fclose(ptr);
		}
	
}
void oldCustomer(){
		 	int pno,k;
		printf("Enter the phone=");
		  	scanf("%d",&pno);
		k=check(pno);
		struct customer r;
		if(k==0)
		{
			printf("\n not registerd,, register first...");
			createNewCustomer();
		}
		else
		{
			
		FILE *ptr;
		ptr=fopen("rec.txt","r");
			while(fread(&r,sizeof(r),1,ptr)){
				
					printf("\n %s %d %s",r.name,r.mobileNo,r.address);

				
				
	}  
	fclose(ptr);
		}
}

void registerProduct()
	{
		struct product  m;
		FILE *ptr;
		int i=1;
		
		ptr=fopen("product1.txt","a");	
		
		while(i)
		{
			
				fflush(stdin);
				printf("\n Enter the product name=");
				  gets(m.fname);
				
				fflush(stdin);
				printf("\n Enter the product price=");
				  scanf("%d",&m.price);
				fflush(stdin);
				
				printf("\n Enter the product category=");
				  gets(m.category);
				
				fflush(stdin);
				
				fwrite(&m,sizeof(m),1,ptr);
				  		printf("\n Hey %s record are  register successfully....",m.fname);

	
			printf("Press 1: for more product: else 0:");
			  scanf("%d",&i);
		}
		fclose(ptr);	  
		
	}
	
	void displayProduct(){
		struct product m;
		FILE *ptr;
		ptr=fopen("product1.txt","r");
		
		while(fread(&m,sizeof(m),1,ptr))
		{
			printf("\n %s %d %s",m.fname,m.price,m.category);
		}
        fclose(ptr);
	}
	
	void deleteProduct(){
		
		char dname[10];
    printf("Enter the product name to delete: ");
    fflush(stdin);
    gets(dname);

    FILE *ptr, *temp;
    struct product m;
    int found=0;

    ptr=fopen("product1.txt","r");
    if(ptr==NULL){ printf("No products to delete"); 
	return; 
	}

    temp=fopen("temp.txt","w");
    while(fread(&m,sizeof(m),1,ptr)) {
        if(strcmp(m.fname, dname)!=0)
            fwrite(&m,sizeof(m),1,temp);
        else
            found=1;
    }
    fclose(ptr);
    fclose(temp);
    remove("product1.txt");
    rename("temp.txt","product1.txt");

    if(found)
        printf("Product deleted successfully.");
    else
        printf("Product not found.");
}
	
	
	void editProduct(){
		char ename[10];
        printf("Enter the product name to edit: ");
         fflush(stdin);
         gets(ename);

         FILE *ptr, *temp;
        struct product m;
        int found=0;
        ptr=fopen("product1.txt","r");
        if(ptr==NULL) {
		 printf("No products to edit");
		  
		  }
       temp=fopen("temp1.txt","w");
       while(fread(&m,sizeof(m),1,ptr)) {
          if(strcmp(m.fname, ename)==0){
            found=1;
            printf("Edit Product Details: ");
            printf("Enter new name: ");
            fflush(stdin);
            gets(m.fname);
            printf("Enter new price: ");
            scanf("%d",&m.price);
            fflush(stdin);
            printf("Enter new category: ");
            gets(m.category);
          }
         fwrite(&m,sizeof(m),1,temp);
       } 
      fclose(ptr);
      fclose(temp);
      remove("product1.txt");
      rename("temp1.txt","product1.txt");
      if(found)
         printf("Product edited successfully.");
      else
        printf("Product not found.");
	  }
int main()
{
int type,i=1;
int choice,x;
int count=0;
while(i){
	again: 
printf("\n Press 1: For Admin...");
printf("\n Press 2: For Customer..");
scanf("%d",&type);
 if (type==1){
    	
 	 x=verifiedAdmin();
	    if(x==1)
	    {
			 	// after verification
			printf("\n welcome Admin=");
		do{
		
		 	printf("\n Press 1 for product registraion=:");
		 	printf("\n Press 2 for product display=:");
			printf("\n Press 3 for product delete=:");
			printf("\n Press 4 for product edit=:");
		printf("\n Enter your choice=:");
				scanf("%d",&choice);
			switch(choice){
			case 1:
				registerProduct();
				break;
			case 2:
				displayProduct();
				break;
			case 3 :
				deleteProduct();
				break;
			case 4:
		     	editProduct();
		     	break;
			case 5:
				printf("exit...");
				break;	
			default:
				printf("\n Wrong Choice..");
	    }
	   }while(choice!=5);
	   return 0;
	}
					
 }
 else if(type=2){
 	printf("\n Press 1: For new customer");
 	printf("\n Press 2: For old customer");
 	scanf("%d",&choice);
 	
 	if(choice==1){
 		createNewCustomer();
	 }
    else if(choice==2){
    oldCustomer();
		
	}
	else{
		printf("invalid choice ,try again");
	}
 }
    else {
        printf("try again");
        goto again;
 }
             printf("Press 1: for more : else 0:");
			  scanf("%d",&i);
	
} 
   printf("\n Exit from system...."); 
}
