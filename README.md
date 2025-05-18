# recipe-calc

## What it is

It's a basic calculating tool for crafting chains, mostly for Factorio.
And it's not nearly finished, I'm working on it :3

## How to use

1. ``make run exe=<your executable name here>``
2. ``./<your executable> help`` to list all available commands (more to come than just 4)
3. enjoy

## How to add more recipes

For now you have to modify the `load_recipes()` function in `main.cpp`.<br>
A recipe takes the form <br>
{ <br>
&ensp;&ensp;get_item_with_amount("\<item id of crafting result>", \<amount>),<br>
&ensp;&ensp;{<br>
&ensp;&ensp;&ensp;&ensp;get_item_with_amount("\<item id of ingredient>", \<amount>), &ensp;&ensp;&ensp;&ensp;// repeat line for every ingredient<br>
&ensp;&ensp;}<br>
}

## How to add more items

For now you have to modify the `load_items()` function in `main.cpp`.<br>
A item takes the form <br>
{<br>
&ensp;&ensp;\<some unique item id>,<br>
&ensp;&ensp;{<br>
&ensp;&ensp;&ensp;&ensp;"\<the same item id>",<br>
&ensp;&ensp;&ensp;&ensp;"\<the item name, purely cosmetic>",<br>
&ensp;&ensp;&ensp;&ensp;0,&ensp;&ensp;&ensp;&ensp;// a placeholder for the amount<br>
&ensp;&ensp;&ensp;&ensp;true (if the item doesn't have a recipe), false (if the item has a recipe)<br>
&ensp;&ensp;}<br>
}


Happy crafting!