# Test Script for Schedule Add/Remove Functionality

## Testing Schedule Management

### Test 1: Add Schedule
```
CMS> AddSchedule
```
**Expected Output**: Creates Schedule with ID 7 and creates Schedule7.csv

### Test 2: Add Another Schedule  
```
CMS> AddSchedule
```
**Expected Output**: Creates Schedule with ID 8 and creates Schedule8.csv

### Test 3: Remove Middle Schedule
```
CMS> RmSchedule 4
```
**Expected Output**: 
- Removes Schedule 4
- Renames Schedule 5 ? Schedule 4 (file: Schedule5.csv ? Schedule4.csv)
- Renames Schedule 6 ? Schedule 5 (file: Schedule6.csv ? Schedule5.csv)  
- Renames Schedule 7 ? Schedule 6 (file: Schedule7.csv ? Schedule6.csv)
- Renames Schedule 8 ? Schedule 7 (file: Schedule8.csv ? Schedule7.csv)
- Updates schedules.csv to remove the last entry

### Test 4: Verify Re-indexing
```
CMS> PrintSchedules
```
**Expected Output**: Shows consecutive schedule IDs: 1, 2, 3, 4, 5, 6, 7

## File System Verification

After each operation, these files should be updated automatically:
- `schedules.csv` - main schedule index
- `ScheduleX.csv` - individual schedule files with consecutive numbering