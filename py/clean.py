import os

files = os.listdir(os.getcwd())
if 'main.exe' in  files:
    os.remove(os.getcwd()+os.sep+'main.exe')
if 'obj' in files and len(os.listdir(os.getcwd()+os.sep+'obj')) > 0:
  for file in os.listdir(os.getcwd()+os.sep+'obj'):
    os.remove(os.getcwd()+os.sep+'obj'+os.sep+file)