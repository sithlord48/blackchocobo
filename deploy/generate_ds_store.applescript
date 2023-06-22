on run argv
  set image_name to item 1 of argv

  tell application "Finder"
  tell disk image_name

    -- wait for the image to finish mounting
    set open_attempts to 0
    repeat while open_attempts < 4
      try
        open
          delay 1
          set open_attempts to 5
        close
      on error errStr number errorNumber
        set open_attempts to open_attempts + 1
        delay 10
      end try
    end repeat

    -- open the image the first time and save a DS_Store with just
    -- background and icon setup
    open
      set current view of container window to icon view
      set theViewOptions to the icon view options of container window
      set background picture of theViewOptions to file ".background:background.png"
      set arrangement of theViewOptions to not arranged
      set icon size of theViewOptions to 192
      set text size of theViewOptions to 16
    close

    open
      tell container window
        set sidebar width to 0
        set statusbar visible to false
        set toolbar visible to false
        set the bounds to { 400, 100, 1200, 725 }
        set position of item "Black_Chocobo.app" to { 0, 325 }
        set position of item "Applications" to { 550, 325 }
      end tell
    close
  end tell
end tell
end run
