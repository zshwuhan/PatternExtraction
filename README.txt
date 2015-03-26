Constraint OPtimized Prefixspan for Epidemiolgical Research (COPPER):
	Author: Agustin Guevara Cogorno
	Supervisor: Hugo Alatrista Salas
	Employer: Pontificia Universidad Católica del Perú (PUCP) - Applied Artificial Intelligence and Pattern Recognition Research Group (GRPIAA)
	License: GNU General Public License v3.0
	
Usage:
	-For the time being only through command line
	-Syntax:
		prefixSpan.exe input_file threshold[%] [-include logic_expression] [-minSseq /-maxSseq/-minSize/-maxSize int_value]
		
		*Optional parameters and flags indicated on brackets
		*Threshold/Minimum Support can be given as whole number or as percentage (i.e. 50%)
		*Inclusion expression accepts binary operator '|' '&' 'v' '^', must contain no spaces and may contain parenthesis, brackets and/or curly braces
		*Any combination of the last set of options may be set in any desired order (i.e. -maxSseq 20 -minSseq 5)
		
	-Input File:
		*One sequence per line
		*No space in between
		*A sequence is defined as succesion of itemsets
		*An itemset contains at least one item, multiple items are comma separated
		*An item is of the form int:int (i.e. 15:22); the first value corresponds to the variable identifier, the second it's respective value
			no two items in an itemset may contain the same variable identifier.
		*Example Data Sets are provided