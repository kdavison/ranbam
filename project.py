#!/usr/bin/env python3

import argparse
import os
import sys
import shutil
import multiprocessing

def get_script_path():
  return os.path.dirname(os.path.realpath(sys.argv[0]))

def get_build_path():
  return get_script_path() + '/build'

def create_build_path():
  path=get_build_path()
  if not os.path.isdir(path):
    try:
      os.makedirs(path)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise

def clean(args):
  print('cleaning all...')
  path=get_build_path()
  if(os.path.isdir(path)):
    try:
      shutil.rmtree(path)
    except OSError as e:
      raise

def generate(args):
  print('generating project...')
  create_build_path()
  try:
    os.chdir(get_build_path())

    cmake_command = \
      'cmake ' + \
      '-GNinja ' + \
      '-DCMAKE_C_COMPILER=clang ' + \
      '-DCMAKE_CXX_COMPILER=clang++ ' + \
      '..'

    os.system( cmake_command )

  except OSError as e:
    raise

def build(args):
  CMAKE_BUILD_TYPE="Debug"
  print('building...')
  create_build_path()
  try:
    cores=multiprocessing.cpu_count() + 2
    if len(args.project) == 1:
      print('\t %s with %d threads' % (' '.join(map(str, args.project)), cores))
      os.system('ninja -C build -j%d %s' % (cores, ' '.join(map(str,args.project))))
    elif len(args.project) > 1:
      print('\t (%s) with %d threads' % (', '.join(map(str, args.project)),cores))
      os.system('ninja -C build -j%d %s' % (cores, ' '.join(map(str,args.project))))
    else:
      print('\t everything with %d threads' % (cores))
      os.system('ninja -C build -j%d' % (cores))
  except OSError as e:
    raise

commands = {
    'clean' : clean,
    'generate' : generate,
    'build' : build
  }

parser = argparse.ArgumentParser(prog='project')
subcommands = parser.add_subparsers(title='commands', dest='command')
subcommands.add_parser('clean')
subcommands.add_parser('generate')
build_parser = subcommands.add_parser('build', help='builds all or specified list of projects')
build_parser.add_argument('project', nargs='*', help='project to build')

args = parser.parse_args()

commands[args.command](args)
