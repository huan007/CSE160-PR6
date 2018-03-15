#! /bin/bash
parallel -j 4 --link ./blockd :::: size.list :::: count.list 5
