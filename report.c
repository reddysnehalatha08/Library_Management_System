#include <stdio.h>
#include "issue.h"
#include "file_utils.h"

void show_reports(void)
{
    FILE *fp;
    Issue issue;
    int total = 0;
    int returned = 0;
    int active = 0;
    float fine = 0;

    fp = fopen(ISSUE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No issue records available.\n");
        return;
    }

    while (fread(&issue, sizeof(Issue), 1, fp) == 1)
    {
        total++;
        fine += issue.fine;

        if (issue.returned)
            returned++;
        else
            active++;
    }

    fclose(fp);

    printf("\n========== Library Report ==========\n");
    printf("Total issue records : %d\n", total);
    printf("Currently issued    : %d\n", active);
    printf("Books returned      : %d\n", returned);
    printf("Total fine          : Rs. %.2f\n", fine);
    printf("====================================\n");
}
