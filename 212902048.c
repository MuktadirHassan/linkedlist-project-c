
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Objective: create a recipe storing applicaiton with ingredients and instructions
  Data structure: Linked list
  Input: recipe name, ingredients, instructions

  Funcitonalities:
  1. add recipe
    1a. add ingredient
    1b. add instruction
  2. delete recipe
  3. search recipe
  4. display all recipes
  5. export recipes to file


  Structure:
    - Recipe: linkedList
      - Recipe name: string
      - Ingredients: linkedList
        - Ingredient: string

      for future
      - Instructions: linkedList
        - Instruction: string


*/

typedef struct recipe
{
  char *name;
  struct ingredient *ingredients;
  struct recipe *next;
} recipe;

typedef struct ingredient
{
  char *name;
  struct ingredient *next;
} ingredient;

// 1. add recipe
// 1a. add ingredient
// 1b. add instruction

// create recipe node
recipe *createRecipe(char *name)
{
  recipe *newRecipe = (recipe *)malloc(sizeof(recipe));
  newRecipe->name = name;
  newRecipe->ingredients = NULL;
  newRecipe->next = NULL;
  return newRecipe;
}

// create ingredient node
ingredient *createIngredient(char *name)
{
  ingredient *newIngredient = (ingredient *)malloc(sizeof(ingredient));
  newIngredient->name = name;
  newIngredient->next = NULL;
  return newIngredient;
}

void specialFormattedPrint(char *str)
{
  printf("\n--------------------\n");
  printf("%s", str);
  printf("\n--------------------\n");
}

/*
  Function: addRecipe
  Description: create recipe node and add to linked list
*/
recipe *addRecipe(recipe **head, char *name)
{
  recipe *newRecipe = createRecipe(name);
  if (*head == NULL)
  {
    *head = newRecipe;
  }
  else
  {
    recipe *temp = *head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newRecipe;
  }
  printf("%s added successfully\n", name);
  return newRecipe;
}
void addIngredient(recipe *head, char *name)
{
  ingredient *newIngredient = createIngredient(name);
  if (head->ingredients == NULL)
  {
    head->ingredients = newIngredient;
  }
  else
  {
    ingredient *temp = head->ingredients;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newIngredient;
  }
}

/*
  Function: handleAddRecipe
  Description: add recipe to linked list
  1. create recipe node
  2. add recipe node to linked list
  3. print recipe added successfully
  4. ask user to add ingredient
  5. add ingredient to linked list

*/

void handleAddRecipe(recipe **head)
{
  char *name = (char *)malloc(sizeof(char) * 100);
  printf("Enter recipe name: ");
  fflush(stdin);
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';

  // add recipe
  recipe *newRecipe = createRecipe(name);
  if (*head == NULL)
  {
    *head = newRecipe;
  }
  else
  {
    recipe *temp = *head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newRecipe;
  }
  printf("%s added successfully\n", name);

  // add ingredient
  do // loop until user enters 'q'
  {
    char *ingredientName = (char *)malloc(sizeof(char) * 100);
    printf("Enter ingredient name (enter 'q' to quit): ");
    fflush(stdin);
    fgets(ingredientName, 100, stdin);
    ingredientName[strlen(ingredientName) - 1] = '\0';

    if (strcmp(ingredientName, "q") == 0)
    {
      break;
    }
    else
    {
      addIngredient(newRecipe, ingredientName);
    }
  } while (1);
}

void handleDisplayRecipe(recipe **head)
{
  if (head == NULL)
  {
    printf("No recipe found\n");
    return;
  }
  else
  {
    recipe *temp = *head;
    specialFormattedPrint("Recipes\n");
    while (temp != NULL)
    {
      printf("Recipe Name: %s\n", temp->name);
      ingredient *ingredient = temp->ingredients;
      printf("Ingredients: \n");
      while (ingredient != NULL)
      {
        printf("\t%s\n", ingredient->name);
        ingredient = ingredient->next;
      }
      temp = temp->next;
    }
  }
}

// 2. delete recipe
void deleteRecipe(recipe **head, char *name)
{
  if (*head == NULL)
  {
    printf("No recipe found\n");
    return;
  }
  else
  {
    recipe *temp = *head;
    if (strcmp(temp->name, name) == 0)
    {
      *head = temp->next;
      free(temp);
      printf("%s deleted successfully\n", name);
      return;
    }
    while (temp->next != NULL)
    {
      if (strcmp(temp->next->name, name) == 0)
      {
        recipe *temp2 = temp->next;
        temp->next = temp->next->next;
        free(temp2);
        printf("%s deleted successfully\n", name);
        return;
      }
      temp = temp->next;
    }
    printf("%s not found\n", name);
  }
}

void handleDeleteRecipe(recipe **head)
{
  char *name = (char *)malloc(sizeof(char) * 100);
  printf("Enter recipe name: ");
  fflush(stdin);
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';

  deleteRecipe(head, name);
}

// search for a recipe
void searchRecipe(recipe **head, char *name)
{
  if (*head == NULL)
  {
    printf("No recipe found\n");
    return;
  }
  else
  {
    recipe *temp = *head;
    while (temp != NULL)
    {
      if (strcmp(temp->name, name) == 0)
      {
        printf("%s found\n", name);
        // display that recipe
        specialFormattedPrint("Recipe\n");
        printf("Recipe Name: %s\n", temp->name);
        ingredient *ingredient = temp->ingredients;
        printf("Ingredients: \n");
        while (ingredient != NULL)
        {
          printf("\t%s\n", ingredient->name);
          ingredient = ingredient->next;
        }
        return;
      }
      temp = temp->next;
    }
    printf("%s not found\n", name);
  }
}

void handleSearchRecipe(recipe **head)
{
  char *name = (char *)malloc(sizeof(char) * 100);
  printf("Enter recipe name: ");
  fflush(stdin);
  fgets(name, 100, stdin);
  name[strlen(name) - 1] = '\0';

  searchRecipe(head, name);
}

// export to excel
void exportToFile(recipe **head)
{
  if (*head == NULL)
  {
    printf("No recipe found\n");
    return;
  }
  else
  {
    FILE *file = fopen("recipe.csv", "w");
    if (file == NULL)
    {
      printf("Error opening file\n");
      return;
    }
    recipe *temp = *head;
    fprintf(file, "Recipe Name,Ingredients\n");
    while (temp != NULL)
    {
      fprintf(file, "%s,", temp->name);
      ingredient *ingredient = temp->ingredients;
      while (ingredient != NULL)
      {
        fprintf(file, "%s,", ingredient->name);
        ingredient = ingredient->next;
      }
      fprintf(file, "\n");
      temp = temp->next;
    }
    fclose(file);
    printf("File exported successfully\n");
  }
}
int main(void)
{

  // create recipe
  // create ingredient
  // add ingredient to recipe
  // add recipe to recipe list
  int choice;
  printf("\n\n--- Welcome ---\n\n");
  recipe *head = NULL;
  do
  {
    // Propmt user with a menu of options
    // 1. add recipe
    // 2. delete recipe
    // 3. search recipe
    // 4. display all recipes
    // 5. export recipes to file
    // 6. quit

    printf("\n1. Add Recipe");
    printf("\n2. Delete Recipe");
    printf("\n3. Search Recipe");
    printf("\n4. Display All Recipes");
    printf("\n5. Export Recipes to File");
    printf("\n6. Add Random Recipe");
    printf("\n7. Quit");
    specialFormattedPrint("Enter your choice: ");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      // add recipe
      handleAddRecipe(&head);
      break;
    case 2:
      // delete recipe
      handleDeleteRecipe(&head);
      break;
    case 3:
      handleSearchRecipe(&head);
      // search recipe
      break;
    case 4:
      handleDisplayRecipe(&head);
      // display all recipes
      break;
    case 5:

      // export recipes to file
      exportToFile(&head);
      break;
    case 6:
      // add random recipe
      recipe *ptr1 = addRecipe(&head, "Recipe 1");
      addIngredient(ptr1, "Ingredient 1");
      addIngredient(ptr1, "Ingredient 2");
      addIngredient(ptr1, "Ingredient 3");
      addIngredient(ptr1, "Ingredient 4");
      addIngredient(ptr1, "Ingredient 5");

      recipe *ptr2 = addRecipe(&head, "Recipe 2");
      addIngredient(ptr2, "Ingredient 1");
      addIngredient(ptr2, "Ingredient 2");
      addIngredient(ptr2, "Ingredient 3");
      addIngredient(ptr2, "Ingredient 4");
      addIngredient(ptr2, "Ingredient 5");

      recipe *ptr3 = addRecipe(&head, "Recipe 3");
      addIngredient(ptr3, "Ingredient 1");
      addIngredient(ptr3, "Ingredient 2");
      addIngredient(ptr3, "Ingredient 3");
      addIngredient(ptr3, "Ingredient 4");
      addIngredient(ptr3, "Ingredient 5");

      recipe *ptr4 = addRecipe(&head, "Recipe 4");
      addIngredient(ptr4, "Ingredient 1");
      addIngredient(ptr4, "Ingredient 2");
      addIngredient(ptr4, "Ingredient 3");
      addIngredient(ptr4, "Ingredient 4");
      addIngredient(ptr4, "Ingredient 5");

      break;
    case 7:
      // quit
      printf("\n\n--- Goodbye ---\n\n");
      break;
    default:
      printf("\nInvalid choice. Please try again.");
      break;
    }

  } while (choice != 7);

  return 0;
}