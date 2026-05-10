void liveSearch() {
    string query = "";
    int resCursor = 0; // which result the >> is on

    while (true) {
        // build results from query
        vector<Node*> results;
        Node* temp = head;
        do {
            if (query.empty() || containsCI(temp->name, query))
                results.push_back(temp);
            temp = temp->next;
        } while (temp != head);

        // keep cursor in bounds
        if (resCursor >= (int)results.size())
            resCursor = max(0, (int)results.size() - 1);

        // draw
        cls();
        cout << "=== Search ===\n\n";
        cout << "  / " << query << "_\n\n"; // search bar

        if (results.empty()) {
            cout << "  no results for \"" << query << "\"\n";
        } else {
            for (int i = 0; i < (int)results.size(); i++) {
                cout << (i == resCursor ? " >> " : "    ");
                cout << results[i]->name;
                if (results[i] == nowPlaying) {
                    if (isPlaying)     cout << "  [playing]";
                    else if (isPaused) cout << "  [paused]";
                }
                cout << "\n";
            }
        }

        cout << "\ntype=search  UP/DOWN=move  ENTER=play  BKSP=delete  ESC=back\n";

        // input
        int key = _getch();
        if (key == 224) {
            int k2 = _getch();
            if (k2 == 72 && resCursor > 0) resCursor--;       // UP
            else if (k2 == 80 && resCursor < (int)results.size()-1) resCursor++; // DOWN
        } else if (key == 13 && !results.empty()) { // ENTER - play
            PlaySound(NULL, NULL, 0);
            PlaySound(results[resCursor]->filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            nowPlaying = results[resCursor];
            isPlaying  = true;
            isPaused   = false;
            g_start    = timeGetTime();
        } else if (key == 27) { // ESC - back
            return;
        } else if (key == 8) { // BACKSPACE
            if (!query.empty()) query.pop_back();
            resCursor = 0;
        } else if (key >= 32 && key <= 126) { // typing
            query += (char)key;
            resCursor = 0;
        } else if (toupper(key) == 'P') {
            togglePause();
        }
    }
}
