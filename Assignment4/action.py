from persistence import *

import sys

def main(args : list[str]):
    #inputfilename : str = args[1]
    inputfilename = "action.txt"

    with open(inputfilename) as inputfile:
        for line in inputfile:
            splittedline : list[str] = line.strip().split(", ")
            product = repo.products.find(id=splittedline[0])
            if (int(splittedline[1]) != 0 and product[0].quantity+int(splittedline[1]) >0):
                newQuantity = product[0].quantity+int(splittedline[1])
                repo.activities.insert(Activitie(splittedline[0],splittedline[1],splittedline[2],splittedline[3]))
                stmt = 'UPDATE products SET quantity = {} WHERE id = {}' .format(newQuantity,product[0].id)
                repo.execute_command(stmt)
                

if __name__ == '__main__':
    main(sys.argv)