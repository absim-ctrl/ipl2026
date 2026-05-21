//write a program to store n records in binary file
//Write a func to get m^th record n display
//use fseek
//write func to delete record
#include<stdio.h>
#include<stdlib.h>
struct Student{
    int id;
    char name[100];
    float marks;
};
void addRecords(){
    struct Student s;
    FILE *fp;//file is a datatype for file handling 
    int n;
    printf("Enter the number of records to be added:\n");
    scanf("%d",&n);
    if(n<=0){
        printf("Invalid number!");
        return ;
    }
    fp=fopen("data.bin","wb");
    if(fp==NULL){
        printf("File error\n");
        return ;
    }
    for(int i=0;i<n;i++){
        printf("Enter id, name, marks of student%d: \n",i+1);
        scanf("%d%s%f",&s.id,s.name,&s.marks);
        fwrite(&s,sizeof(s),1,fp);
    }
    fclose(fp);
}
void getRecord(){
    struct Student s;
    FILE *fp;
    int m;
    fp=fopen("data.bin","rb");
    if(fp==NULL){
        printf("File error\n");
        return ;
    }
    printf("Enter the record number to fetch:\n");
    scanf("%d",&m);
    if(m<=0){
        printf("invalid record number entered!");
        fclose(fp);
        return ;
    }
    //SEEK_SET->strts from beginning of file(moves to start)
    //offset->num of bytes to move each record has ifxed size
    //fseek(file_pointer,offset,position);->jumps directly to the mth record rather than chacking for all the records using loop
    fseek(fp,(m-1)*sizeof(s),SEEK_SET);
    fread(&s,sizeof(s),1,fp);
    printf("\nRecord %d\n : ",m);
    printf("ID: %d\nName: %s\nMarks: %.2f\n",s.id,s.name,s.marks);
    fclose(fp);
}
void deleteRecord(){
    struct Student s;
    FILE *fp;
    FILE *newfile;
    newfile=fopen("data1.bin","wb");
    fp=fopen("data.bin","rb");
    if((fp==NULL)||(newfile==NULL)){
        printf("File error\n");
        return ;
    }
    
    int recid;
    printf("Enter ID to be deleted?");
    scanf("%d",&recid);
    int found=0;
    while(fread(&s,sizeof(s),1,fp)){
        if(s.id!=recid)
            fwrite(&s,sizeof(s),1,newfile);
        else{
            found=1;
        }
    }
    if(found==0){
        printf("Record not found");
    }else {
        printf("Record deleted successfully");
    }
    fclose(fp);
    fclose(newfile);
    remove("data.bin");
    rename("data1.bin","data.bin");
}


int main(){
    
    int choice;
    while(1){
    printf("Enter the choice :");
    scanf("%d",&choice);
    
    switch(choice){
        case 1:addRecords();
        break;
        case 2:getRecord();
        break;
        case 3:deleteRecord();
        break;
        case 4:exit(0);
        break;
        default:printf("Invalid choice");
    }
}
    return 0;
}


