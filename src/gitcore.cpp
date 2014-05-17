/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "gitcore.h"
#include <QDebug>

gitCore::gitCore(QObject* parent): QObject(parent)
{

  git_threads_init();
}

gitCore::~gitCore()
{
  git_threads_shutdown();
}

void gitCore::addDirectory(QString dir)
{
 is_git_dir(dir);

  
}

void gitCore::removeDirectory(QString dir)
{

}

bool gitCore::is_git_dir(QString path)
{
  git_repository *e;
  int res = git_repository_open_ext( &e, path.toStdString().data(), 0, ".");
  switch( res )
  {
    case 0:
    {
      _repoList.append( new QRepo (e, path) );
      emit newRepository(path);
      return true;
    }
      break;
    default:
      qDebug() << "Not found git repository";
  }
}

void gitCore::updateAllRepo()
{
  QString program = "git";
   QStringList arguments;
  for ( int i =0 ; i< _repoList.size(); i++)
  {
    arguments.clear();
    arguments << "pull";
    
    
    
    QProcess *myProcess = new QProcess(this);
    myProcess->setWorkingDirectory(_repoList[i]->getDirPath());
    myProcess->start(program, arguments);
   
    myProcess->waitForFinished();
    qDebug() << "Git Pull Finished :: "  << _repoList[i]->getDirPath();
  }
    
//   git_merge_result *out;
//   git_reference *our_ref, *their_ref;
//   git_merge_head *their_heads[1];
//   git_merge_opts opts;
//   git_remote *remote = NULL;
//   
//   bool automerge = true;
//   opts.merge_tree_opts.automerge_flags= GIT_MERGE_AUTOMERGE_NORMAL;
//   
//   int res = 0;
//   qDebug() << "Going to pull";
//   
//   for (int i = 0 ; i< _repoList.size() ; i++ )
//   {
// 
//     git_strarray ref_list;
//     git_reference_list(&ref_list, _repoList[i]);
// 
//     const char *refname;
//     git_reference *ref;
//     for (int j = 0; j < ref_list.count; ++j) 
//     {
//       refname = ref_list.strings[i];
//       qDebug() << "Refrence Name ::  " << QString::fromUtf8(refname);
//     }
// 
//           qDebug() << "*********** TAG LIST ***********  ";
// 
//         git_strarray tag_list;
// 	git_tag_list(&tag_list,_repoList[i] );
// 
// 	for (int j = 0; j < tag_list.count; ++j) 
//     {
//       qDebug() << "TAG Name ::  " << QString::fromUtf8(*tag_list.strings);
//     }
// 
//     git_strarray *remotelist;
// 
//   res = git_remote_list(remotelist ,_repoList[i]);
//   qDebug() << "REMOTE LIST COUNT :: " << remotelist->count ;
// //   qDebug() << "REMOTE NAME TAMOM SHOD ";
//   if (res == 0 )
//   {
//     qDebug() << "List Remote gerefteh shod :: ";
//   for ( int j = 0; j < remotelist->count ; j++ )
//   {
//     qDebug() << "REMOTE NAME :: " << QString::fromUtf8( *remotelist[j].strings );
//   }
//   }
//   else
//     qDebug() << "list remote daryaft nashod";
//     
//   }
//   
//   git_strarray *remotelist2;
//   
//   for (int i = 0 ; i< _repoList.size() ; i++ )
//   {
// 
//  
// //     git_reference_lookup(&their_ref, _repoList[i], "refs/remotes/origin/master");
// //     git_merge_head_from_ref(&their_heads[0], _repoList[i], their_ref);
// //     res = git_merge(&out, _repoList[i], (const git_merge_head **)their_heads, 1, &opts );
//     res = git_remote_load(&remote, _repoList[i],"origin");
//     qDebug() << "RES :::::: " << res;
//       if ( res==0 )
//       {
//   
// 	if (git_remote_create_inmemory(&remote, _repoList[i], NULL, "origin") < 0)
// 	{
// 	  qDebug() << "Nashod ke beshe";
// 	} else {
// 	  qDebug() << "shod ke beshe dar memory";
// 	  if ( git_remote_connect(remote, GIT_DIRECTION_FETCH) < 0 )
// 	  {
// 	    qDebug() << "Not connected !";
// 	  } else {
// 	    qDebug() << "connected OK";
// 	    if (git_remote_download(remote) < 0) 
// 	    {
// 	      qDebug() << "Download nashod !";
// 	    } else {
// 	      qDebug() << "Download kardim ... ";
// 	        git_remote_disconnect(remote);
// 	    }
// 	  }
// 		        git_remote_disconnect(remote);
// 
// 	}
//       } else {
// 	qDebug() << "REMOTE LOAD BE MOSHKEL KHORD";
//       }
// 
// 
//     qDebug() << "Results :: " << res;
//   }
}

QList< QRepo* > gitCore::getRepoList()
{
  return _repoList;
}

#include "gitcore.moc"
