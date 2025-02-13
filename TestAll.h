#pragma once
#include "Graph.h"
#include <cassert>
#include <string>



void testDefaultConstructor();
void testPrepend();
void testAdd();
void testGet();
void testGetLength();

void testHashTableAddAndFind();
void testHashTableDelete();
void testHashTableSize();
void testHashTableEmpty();
void testHashTableRehashing();
void testHashTableKeys();
void testHashTableDeleteWithKeys();

void testGraphGetVertexById();
void testGraphAddEdge();
void testGraphDeleteVertex();
void testGraphSetNodeData();
void testGraphDeleteEdge();
void testGraphFindMaxBandwidthPath();
void testGraphFindShortestRoute();