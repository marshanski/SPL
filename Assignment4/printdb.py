from persistence import *

def main():

    '''activities '''
    print("Activities ")
    activities           = repo.activities .find_all()
    stmt                 = 'SELECT * FROM activities  ORDER BY date ASC' 
    activitiesSorted     = repo.execute_command(stmt)
    for activities  in activitiesSorted:
        print(str(Activitie(activities[0],activities[1],activities[2],activities[3])))

    '''BRANCES'''
    print("Branches")
    branches          = repo.branches.find_all()
    stmt              = 'SELECT * FROM branches ORDER BY id ASC' 
    branchesSorted    = repo.execute_command(stmt)
    for branch in branchesSorted:
        print(str(Branche(branch[0],branch[1],branch[2])))

    '''Employees'''
    print("Employees")
    employees           = repo.employees.find_all()
    stmt                = 'SELECT * FROM employees ORDER BY id ASC' 
    employeeSorted      = repo.execute_command(stmt)
    for employee in employeeSorted:
        print(str(Employee(employee[0],employee[1],employee[2],employee[3])))

    '''Products'''
    print("Products")
    products           = repo.products.find_all()
    stmt                = 'SELECT * FROM products ORDER BY id ASC' 
    productsSorted      = repo.execute_command(stmt)
    for product in productsSorted:
        print(str(Product(product[0],product[1],product[2],product[3])))

    '''Products'''
    print("Suppliers")
    suppliers            = repo.suppliers.find_all()
    stmt                = 'SELECT * FROM suppliers ORDER BY id ASC' 
    suppliersSorted      = repo.execute_command(stmt)
    for supplier in suppliersSorted:
        print(str(Supplier(supplier[0],supplier[1],supplier[2])))

    '''Employees report'''
    print("\nEmployees report")
    stmt= '''
            SELECT employees.name, employees.salary,branches.location,
            SUM(COALESCE(activities.quantity*products.price*-1,0))
            FROM employees
            JOIN branches        ON employees.branche        = branches.id
            LEFT JOIN activities ON activities.activator_id  = employees.id 
            LEFT JOIN products   ON activities.product_id    = products.id 
            GROUP BY employees.name
            ORDER BY employees.name
            '''

    employeesReport= repo.execute_command(stmt)
    for report in employeesReport:
        print("{} {} {} {}".format(report[0].decode(),report[1],report[2].decode(),report[3]))


    print("\nActivities report")
    stmt= '''
            SELECT activities.date,products.description,activities.quantity,employees.name,suppliers.name
            FROM activities
            LEFT JOIN products    ON  products.id   = activities.product_id
            LEFT JOIN employees   ON  employees.id  = activities.activator_id
            LEFT JOIN suppliers   ON  suppliers.id  = activities.activator_id
            ORDER BY activities.date
            '''
    activitiesReport = repo.execute_command(stmt)
    for report in activitiesReport:
        if report[3]!= None:
            a = str("'{}'".format(report[3].decode()))
        else:
            a = None
        if report[4]!= None:
            b = str("'{}'".format(report[4].decode()))
        else:
            b = None
        print("('{}', '{}', {}, {}, {})".format(report[0].decode(),report[1].decode(),report[2],a,b))
    
    

        



    

if __name__ == '__main__':
    main()