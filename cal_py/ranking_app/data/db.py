from sqlalchemy import *
from sqlalchemy.orm import *

engine = create_engine('sqlite:///data/db.sqlite', echo=False)

metadata = MetaData()
metadata.bind = engine

ranking = Table(
    'ranking', metadata,
    Column('id', Integer, primary_key=True),
    Column('name', String),
    Column('hiScore', Float),
    Column('latestScore', Float)
)


class data():
    """docstring for data."""
    def __init__(self):
        metadata.create_all(engine)
    
    def add(self, personId, personName, score):
        if ranking.select().where(ranking.c.id == personId).execute().fetchone() != None:
            #update
            if ranking.select().where(ranking.c.id == personId).execute().fetchone()[2] > score:
                ranking.update().where(ranking.c.id == personId).execute(latestScore=score, hiScore=score)
            else:
                ranking.update().where(ranking.c.id == personId).execute(latestScore=score)
        else:
            #create new record
            ranking.insert().execute(id=personId, name=personName, latestScore=score, hiScore=score)
            
    def rank(self, personId):
        pass
        
    