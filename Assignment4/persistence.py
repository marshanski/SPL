import sqlite3
import atexit
from dbtools import Dao
 
# Data Transfer Objects:
class Employee(object):
    def __init__(self,id,name,salary,branch):
        self.id     = id
        self.name   = name
        self.salary = salary
        self.branch = branch
 
class Supplier(object):
    def __init__(self,id,name,contact_info):
        self.id       = id
        self.name     = name
        self.salary   = contact_info

class Product(object):
    def __init__(self,id,description,price,,quantity):
        self.id          = id
        self.description = description
        self.price       = price
        self.quantity    = quantity


class Branche(object):
    def __init__(self,id,location,number_of_empolyers):
        self.id       = id
        self.location = location
        self.salary   = number_of_empolyers
    

class Activitie(object):
    def __init__(self,product_id,quantity,activator_id,,date):
        self.product_id   = id
        self.quantity     = quantity
        self.activator_id = activator_id
        self.date          = date
    
 
 
#Repository
class Repository(object):
    def __init__(self):
        self._conn = sqlite3.connect('bgumart.db')
        self._conn.text_factory = bytes
        self.employers          = Employee(self._conn)
        self.activities         = Activitie(self._conn)
        self.branches           = Branche(self._conn)
        self.products           = Product(self._conn)
 
    def _close(self):
        self._conn.commit()
        self._conn.close()
 
    def create_tables(self):
        self._conn.executescript("""
            CREATE TABLE employees (
                id              INT         PRIMARY KEY,
                name            TEXT        NOT NULL,
                salary          REAL        NOT NULL,
                branche    INT REFERENCES branches(id)
            );
    
            CREATE TABLE suppliers (
                id                   INTEGER    PRIMARY KEY,
                name                 TEXT       NOT NULL,
                contact_information  TEXT
            );

            CREATE TABLE products (
                id          INTEGER PRIMARY KEY,
                description TEXT    NOT NULL,
                price       REAL NOT NULL,
                quantity    INTEGER NOT NULL
            );

            CREATE TABLE branches (
                id                  INTEGER     PRIMARY KEY,
                location            TEXT        NOT NULL,
                number_of_employees INTEGER
            );
    
            CREATE TABLE activities (
                product_id      INTEGER REFERENCES products(id),
                quantity        INTEGER NOT NULL,
                activator_id    INTEGER NOT NULL,
                date            TEXT    NOT NULL
            );
        """)

    def execute_command(self, script: str) -> list:
        return self._conn.cursor().execute(script).fetchall()
 
# singleton
repo = Repository()
atexit.register(repo._close)