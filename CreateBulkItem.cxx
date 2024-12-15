#include"CreateBulkItem.hxx"

int ITK_user_main(int argc, char* argv[]) {
	int status = ITK_ok;
	
	tag_t NewFolder = NULLTAG;
	tag_t create_input = NULLTAG;
	tag_t type = NULLTAG;
	tag_t NewItem = NULLTAG;
	tag_t user = NULLTAG;
	tag_t Huser_folder = NULLTAG;

	printf("Utlity Statred.\n");	
	char* userID = ITK_ask_cli_argument("-u=");
	char* uPassword = ITK_ask_cli_argument("-p=");
	char* group = ITK_ask_cli_argument("-g=");

	status = ITK_init_module(userID, uPassword, group);
	if (status == ITK_ok) {
		printf("Login Successful.\n");
	}
	else {
		printf("Failed to Login.\n");
	}

	status = TCTYPE_find_type("Folder", "Folder", &type);	
	status = TCTYPE_construct_create_input(type, & create_input);
	status = AOM_set_value_string(create_input, "object_name", "BulkItem_Side Clamping");
	status = TCTYPE_create_object(create_input, &NewFolder);	
	status = AOM_save_with_extensions(NewFolder);

	

	//find user Home folder	
	status = SA_find_user2(userID, & user);
	status = SA_ask_user_home_folder(user, &Huser_folder);
	status = FL_insert(Huser_folder, NewFolder, 999);	
	status = AOM_save_with_extensions(Huser_folder);	
	
	

	FILE* fp;
	char FLine[50];
	char* ItemName;
	char* UOM;
	char* make_buy;
	fp = fopen("G:\\My Drive\\FaithPLM\\Online Batch Recorded Sessions\\3. C Language\\Bulk Item Creation BOM.csv", "a+");

	while (fgets(FLine, 50, fp)) {
		 ItemName= strtok(FLine, ",");
		 UOM = strtok(NULL, ", ");
		 make_buy = strtok(NULL, " ");

		 /*printf("%s ", ItemName);
		 printf("%s ", UOM);
		 printf("%s\N", make_buy);*/


		 status = TCTYPE_find_type("A3BHMakePart", "A3BHMakePart", &type);
		 status = TCTYPE_construct_create_input(type, &create_input);
		 status = AOM_set_value_string(create_input, "object_name", ItemName);
		 status = AOM_set_value_string(create_input, "uom_tag", UOM);
		 status = AOM_set_value_string(create_input, "a3MakeBuy", make_buy);
		 status = TCTYPE_create_object(create_input, &NewItem);
		 status = AOM_save_with_extensions(NewItem);

		 status = FL_insert(NewFolder, NewItem, 999);		
		 status = AOM_save_with_extensions(NewFolder);
		 printf("Item Created: %d\n", NewItem);

	}

	fclose(fp);
	printf("Utlity completed.\n");
	(void)_getch();
	return status;
}

