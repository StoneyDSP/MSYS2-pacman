#[===[
```
Joins arguments and places the results in ```${result_var}```.
```
]===]
function(join_args result_var)
	set(result "")
	foreach (arg ${ARGN})
	  	set(result "${result}${arg}")
	endforeach ()
	set(${result_var} "${result}" PARENT_SCOPE)
endfunction()
