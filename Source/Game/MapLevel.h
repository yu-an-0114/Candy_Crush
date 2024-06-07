#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
namespace game_framework {
	/*
	class MapLevel {
	public:
		static int map_level[30][10][10];
	};
	*/
	
	static int map_level[30][10][10] = {
		//1
		   {{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1}},
			//2
		   {{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}},
			//3
		   {{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}},
			//4
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //5
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,2,3,4,5,6,7,8,9,10},
			 {0,11,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //6
		   {{1,1,1,1,1,1,1,1,1,1},
			{1,2,3,4,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1}},
			//7
		   {{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}},
			//8
		   {{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}},
			//9
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //10
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //11
			 {{1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1},
			 {1,1,1,1,1,1,1,1,1,1}},
			 //12
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,1,1,1,1,1,1,1,1,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //13
			{{0,0,0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,1,1,1,1,1,1,0,0},
			 {0,0,0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0,0,0}},
			 //14
			 {{0,0,0,0,0,0,0,0,0,0},
			  {0,0,1,1,1,1,1,1,0,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,0,1,1,1,1,1,1,0,0},
			  {0,0,0,0,0,0,0,0,0,0}},
			  //15
			 {{0,0,0,0,0,0,0,0,0,0},
			  {0,0,1,1,1,1,1,1,0,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,1,1,1,1,1,1,1,1,0},
			  {0,0,1,1,1,1,1,1,0,0},
			  {0,0,0,0,0,0,0,0,0,0}},
			  //16
			  {{1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1},
			   {1,1,1,1,1,1,1,1,1,1}},
			   //17
			   {{0,0,0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,1,1,1,0},
				{0,0,0,0,0,0,0,0,0,0}},
				//18
				{ {0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,1,1,1,1,1,1,0,0},
				 {0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0} },
				 //19
				 { {0,0,0,0,0,0,0,0,0,0},
				  {0,0,1,1,1,1,1,1,0,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,1,1,1,1,1,1,1,1,0},
				  {0,0,1,1,1,1,1,1,0,0},
				  {0,0,0,0,0,0,0,0,0,0} },
				  //20
				  { {0,0,0,0,0,0,0,0,0,0},
				   {0,0,1,1,1,1,1,1,0,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,1,1,1,1,1,1,1,1,0},
				   {0,0,1,1,1,1,1,1,0,0},
				   {0,0,0,0,0,0,0,0,0,0} },

				   //21
				   { {0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0,0,1,1,1,1,1,1,0,0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0,0,0,0,0,0,0,0,0,0 } },
					//22
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//23
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//24
					{ {1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1} },
						//25
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//26
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//27
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//28
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,1,1,1,1,1,1,0,0},
					 {0,0,0,0,0,0,0,0,0,0} },
						//29
					{ {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1,1,1} },
						//30
					{ {0,0,0,0,0,0,0,0,0,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,1,1,1,1,1,1,1,1,0},
					 {0,0,0,0,0,0,0,0,0,0} }
	};
};