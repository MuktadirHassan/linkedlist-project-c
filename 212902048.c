
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

void addRecipe(recipe **head, char *name)
{
  recipe *newRecipe = createRecipe(name);
  if (head == NULL)
  {
    head = newRecipe;
  }
  else
  {
    recipe *temp = head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newRecipe;
  }
  printf("%s added successfully\n", name);
}

// void addIngredient(recipe *head, char *name)
// {
//   ingredient *newIngredient = createIngredient(name);
//   if (head->ingredients == NULL)
//   {
//     head->ingredients = newIngredient;
//   }
//   else
//   {
//     ingredient *temp = head->ingredients;
//     while (temp->next != NULL)
//     {
//       temp = temp->next;
//     }
//     temp->next = newIngredient;
//   }
// }

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
    while (temp != NULL)
    {
      specialFormattedPrint("Recipes\n");
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
    printf("\n6. Quit");
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
      break;
    case 3:
      // search recipe
      break;
    case 4:
      handleDisplayRecipe(&head);
      // display all recipes
      break;
    case 5:
      // export recipes to file
      break;
    case 6:
      // quit
      printf("\n\n--- Goodbye ---\n\n");
      break;
    default:
      printf("\nInvalid choice. Please try again.");
      break;
    }

  } while (choice != 6);

  return 0;
}